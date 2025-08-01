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
	}

	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -90.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	if (HasAuthority())
	{
		SetupFsm();
	}
}

void AEmpusa::BeginPlay()
{
	Super::BeginPlay();

	LeftHand->OnComponentBeginOverlap.AddDynamic(this, &AEmpusa::OverlapBegin);
	RightHand->OnComponentBeginOverlap.AddDynamic(this, &AEmpusa::OverlapBegin);

	CollisionArray.SetNum(static_cast<uint8>(EEmpusaCollision::ALL));
	CollisionArray[static_cast<uint8>(EEmpusaCollision::LEFT)] = LeftHand;
	CollisionArray[static_cast<uint8>(EEmpusaCollision::RIGHT)] = RightHand;

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
	EmpusaFsmComp = CreateDefaultSubobject<UFsmComponent>(TEXT("EmpusaFsmComp"));
	EmpusaFsmComp->SetIsReplicated(true);

	EmpusaFsmComp->CreateState(EEmpusaFsm::IDLE,
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
					EmpusaFsmComp->ChangeState(EEmpusaFsm::WALK);
					return;
				}
				else
				{
					EmpusaFsmComp->ChangeState(EEmpusaFsm::RUN);
					return;
				}
			}
		},

		//End
		[this]()
		{
		}
	);

	EmpusaFsmComp->CreateState(EEmpusaFsm::WALK,
		//Start
		[this]()
		{
			Multicast_WalkAnimation();
		},

		//Update
		[this](float DeltaTime)
		{
			TurnToActor(DeltaTime);
			if (HasAuthority())
			{
				auto Result = AiController->MoveToActor(TargetPlayer);
			}

			if (FVector::DistXY(GetActorLocation(), TargetPlayer->GetActorLocation()) > RunEndRange)
			{
				EmpusaFsmComp->ChangeState(EEmpusaFsm::RUN);
				return;
			}

			if (FVector::DistXY(GetActorLocation(), TargetPlayer->GetActorLocation()) <= AttackRange)
			{
				EmpusaFsmComp->ChangeState(EEmpusaFsm::ATTACK);
				return;
			}
		},

		//End
		[this]()
		{
		}
	);


	EmpusaFsmComp->CreateState(EEmpusaFsm::RUN,
		//Start
		[this]()
		{
			Multicast_RunAnimation();
			//RunAnimation();
		},

		//Update
		[this](float DeltaTime)
		{
			TurnToActor(DeltaTime);
			if (HasAuthority())
			{
				auto Result = AiController->MoveToActor(TargetPlayer);
			}

			float Dist = FVector::DistXY(GetActorLocation(), TargetPlayer->GetActorLocation());
			if (Dist <= AttackRange)
			{
				EmpusaFsmComp->ChangeState(EEmpusaFsm::ATTACK);
				return;
			}
		},

		//End
		[this]()
		{
		}
	);

	EmpusaFsmComp->CreateState(EEmpusaFsm::ATTACK,
		//Start
		[this]()
		{
			RandomIndex = FMath::RandRange(RandomMin, RandomMax);
			Multicast_RandomAttack(RandomIndex);
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
						EmpusaFsmComp->ChangeState(EEmpusaFsm::RUN);
						return;
					}
					else if (Dist > AttackRange&& Dist<= RunEndRange)
					{
						EmpusaFsmComp->ChangeState(EEmpusaFsm::WALK);
						return;
					}
					else
					{
						RandomIndex = FMath::RandRange(RandomMin, RandomMax);
						Multicast_RandomAttack(RandomIndex);
					}
				}
			}
		},

		//End
		[this]()
		{
		}
	);

	EmpusaFsmComp->CreateState(EEmpusaFsm::DAMAGED,
		//Start
		[this]()
		{
			Multicast_DamagedAnimation();
		},

		//Update
		[this](float DeltaTime)
		{
			if (bDead)
			{
				EmpusaFsmComp->ChangeState(EEmpusaFsm::DEAD);
				return;
			}

			if (!GetMesh()->GetAnimInstance()->IsAnyMontagePlaying())
			{

				float Dist = FVector::DistXY(GetActorLocation(), TargetPlayer->GetActorLocation());
				if (Dist > AttackRange && Dist > RunEndRange)
				{
					EmpusaFsmComp->ChangeState(EEmpusaFsm::RUN);
					return;
				}
				else if (Dist > AttackRange && Dist <= RunEndRange)
				{
					EmpusaFsmComp->ChangeState(EEmpusaFsm::WALK);
					return;
				}
				else
				{
					EmpusaFsmComp->ChangeState(EEmpusaFsm::ATTACK);
					return;
				}
			}
		},

		//End
		[this]()
		{
		}
	);

	EmpusaFsmComp->CreateState(EEmpusaFsm::DEAD,
		//Start
		[this]()
		{
			Multicast_DeadAnimation();
		},

		//Update
		[this](float DeltaTime)
		{
			if (!GetMesh()->GetAnimInstance()->IsAnyMontagePlaying())
			{
				EmpusaFsmComp->ChangeState(EEmpusaFsm::END);
				return;
			}
		},

		//End
		[this]()
		{
		}
	);

	EmpusaFsmComp->CreateState(EEmpusaFsm::END,
		//Start
		[this]()
		{
			bDestroyed = true;
			SetActorHiddenInGame(true);
			SetActorEnableCollision(false);
			SetActorTickEnabled(false);
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

	EmpusaFsmComp->ChangeState(EEmpusaFsm::IDLE);
}

void AEmpusa::DamagedDefault()
{
	DamagedAnimation();
	if (HasAuthority())
	{
		EmpusaFsmComp->ChangeState(EEmpusaFsm::DAMAGED);
	}
}

void AEmpusa::DamagedGeneral()
{
}

void AEmpusa::DamagedSnatch()
{
	//SnatchAnimation();
}

void AEmpusa::Multicast_RandomAttack_Implementation(int32 Index)
{
	RandomAttack(Index);
}

void AEmpusa::Multicast_RunAnimation_Implementation()
{
	RunAnimation();
}

void AEmpusa::Multicast_DamagedAnimation_Implementation()
{
	DamagedAnimation();
}

void AEmpusa::Multicast_WalkAnimation_Implementation()
{
	WalkAnimation();
}

void AEmpusa::Multicast_DeadAnimation_Implementation()
{
	DeadAnimation();
}

void AEmpusa::Multicast_SnatchAnimation_Implementation()
{
	SnatchAnimation();
}
