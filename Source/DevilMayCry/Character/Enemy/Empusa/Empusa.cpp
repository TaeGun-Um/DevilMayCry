// Fill out your copyright notice in the Description page of Project Settings.


#include "Empusa.h"
#include "Components/CapsuleComponent.h"
#include "Engine/DamageEvents.h" 
#include "../../Player/ParentCharacter.h"
#include "../../DamageType/GeneralDamageType.h"
#include "../../FsmComponent.h"
#include "AIController.h"

#include "GameFramework/Controller.h"
#include "../AI/EnemyController.h"

#include "DrawDebugHelpers.h"

AEmpusa::AEmpusa()
{
	//메시 세팅
	TObjectPtr<USkeletalMesh> SKM = LoadObject<USkeletalMesh>(nullptr, TEXT("/Script/Engine.SkeletalMesh'/Game/Asset/Character/Enemy/Empusa/mesh/EmpusaFix.EmpusaFix'"));

	if (SKM)
	{
		GetMesh()->SetSkeletalMesh(SKM);

		LeftHand = CreateDefaultSubobject<UCapsuleComponent>(TEXT("LeftHand"));
		LeftHand->SetupAttachment(GetMesh(), "L_Hand");
		RightHand = CreateDefaultSubobject<UCapsuleComponent>(TEXT("RightHand"));
		RightHand->SetupAttachment(GetMesh(), "R_Hand");

		CollisionArray.SetNum(static_cast<uint8>(EEmpusaCollision::ALL));
		CollisionArray[static_cast<uint8>(EEmpusaCollision::LEFT)] = LeftHand;
		CollisionArray[static_cast<uint8>(EEmpusaCollision::RIGHT)] = RightHand;
	}

	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -90.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	SetupFsm();
}

void AEmpusa::BeginPlay()
{
	Super::BeginPlay();

	LeftHand->OnComponentBeginOverlap.AddDynamic(this, &AEmpusa::OverlapBegin);
	RightHand->OnComponentBeginOverlap.AddDynamic(this, &AEmpusa::OverlapBegin);
	ToggleCollision(false, EEmpusaCollision::ALL);
}

void AEmpusa::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEmpusa::ToggleCollision(bool Value, uint8 Where)
{
	ToggleCollision(Value, static_cast<EEmpusaCollision>(Where));
}

void AEmpusa::ToggleCollision(bool Value, EEmpusaCollision Where)
{
	if (Where == EEmpusaCollision::ALL)
	{
		for (auto Iter : CollisionArray)
		{
			Iter->SetGenerateOverlapEvents(Value);
		}
	}
	else
	{
		CollisionArray[static_cast<uint8>(Where)]->SetGenerateOverlapEvents(Value);
	}
}

void AEmpusa::OverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this)
	{
		TObjectPtr<AParentCharacter> Enemy = Cast<AParentCharacter>(SweepResult.GetActor());
		if (Enemy != nullptr)
		{
			FDamageEvent DamageEvent(UGeneralDamageType::StaticClass());

			Enemy->TakeDamage(AttackDamage, DamageEvent, GetController(), this);
		}
	}
}

void AEmpusa::SetupFsm()
{
	FsmComp = CreateDefaultSubobject<UFsmComponent>(TEXT("EmpusaFsmComp"));
	FsmComp->SetIsReplicated(true);

	FsmComp->CreateState(EEmpusaFsm::IDLE,
		//Start
		[this]()
		{
		},

		//Update
		[this](float DeltaTime)
		{
			if (TargetPlayer != nullptr)
			{
				if (FVector::DistXY(GetActorLocation(), TargetPlayer->GetActorLocation()) < RunEndRange)
				{
					FsmComp->ChangeState(EEmpusaFsm::WALK);
					return;
				}
				else
				{
					FsmComp->ChangeState(EEmpusaFsm::RUN);
					return;
				}
			}
		},

		//End
		[this]()
		{
		}
	);

	FsmComp->CreateState(EEmpusaFsm::WALK,
		//Start
		[this]()
		{
			WalkAnimation();
		},

		//Update
		[this](float DeltaTime)
		{
			TurnToActor(DeltaTime);
			auto Result = AiController->MoveToActor(TargetPlayer);

			if (FVector::DistXY(GetActorLocation(), TargetPlayer->GetActorLocation()) <= AttackRange)
			{
				FsmComp->ChangeState(EEmpusaFsm::ATTACK);
				return;
			}
		},

		//End
		[this]()
		{
		}
	);


	FsmComp->CreateState(EEmpusaFsm::RUN,
		//Start
		[this]()
		{
			RunAnimation();
		},

		//Update
		[this](float DeltaTime)
		{
			TurnToActor(DeltaTime);
			auto Result = AiController->MoveToActor(TargetPlayer);

			float Dist = FVector::DistXY(GetActorLocation(), TargetPlayer->GetActorLocation());
			if (Dist <= AttackRange)
			{
				FsmComp->ChangeState(EEmpusaFsm::ATTACK);
				return;
			}
		},

		//End
		[this]()
		{
		}
	);

	FsmComp->CreateState(EEmpusaFsm::ATTACK,
		//Start
		[this]()
		{
			RandomAttack();
		},

		//Update
		[this](float DeltaTime)
		{
			if (!GetMesh()->GetAnimInstance()->IsAnyMontagePlaying())
			{
				if (TargetPlayer && LimitAngleOver(LimitAngle))
				{
					TurnToActor(DeltaTime);
				}
				else
				{
					float Dist = FVector::DistXY(GetActorLocation(), TargetPlayer->GetActorLocation());
					if (Dist > AttackRange&& Dist> RunEndRange)
					{
						FsmComp->ChangeState(EEmpusaFsm::RUN);
						return;
					}
					else if (Dist > AttackRange&& Dist<= RunEndRange)
					{
						FsmComp->ChangeState(EEmpusaFsm::WALK);
						return;
					}
					else
					{
						RandomAttack();
					}
				}
			}
		},

		//End
		[this]()
		{
		}
	);

	FsmComp->CreateState(EEmpusaFsm::DAMAGED,
		//Start
		[this]()
		{
		},

		//Update
		[this](float DeltaTime)
		{
			if (!GetMesh()->GetAnimInstance()->IsAnyMontagePlaying())
			{
				float Dist = FVector::DistXY(GetActorLocation(), TargetPlayer->GetActorLocation());
				if (Dist > AttackRange && Dist > RunEndRange)
				{
					FsmComp->ChangeState(EEmpusaFsm::RUN);
					return;
				}
				else if (Dist > AttackRange && Dist <= RunEndRange)
				{
					FsmComp->ChangeState(EEmpusaFsm::WALK);
					return;
				}
				else
				{
					RandomAttack();
				}
			}
		},

		//End
		[this]()
		{
		}
	);

	FsmComp->CreateState(EEmpusaFsm::DEAD,
		//Start
		[this]()
		{
		},

		//Update
		[this](float DeltaTime)
		{
		},

		//End
		[this]()
		{
		}
	);

	FsmComp->ChangeState(EEmpusaFsm::IDLE);
}

void AEmpusa::DamagedDefault()
{
	FsmComp->ChangeState(EEmpusaFsm::DAMAGED);

	DamagedAnimation();
}

void AEmpusa::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
