// Fill out your copyright notice in the Description page of Project Settings.


#include "Angelo.h"
#include "Components/CapsuleComponent.h"
#include "Engine/DamageEvents.h" 
#include "../../Player/ParentCharacter.h"
#include "../../DamageType/GeneralDamageType.h"
#include "../../FsmComponent.h"
#include "AIController.h"

AAngelo::AAngelo()
{
	//메시 세팅
	TObjectPtr<USkeletalMesh> SKM = LoadObject<USkeletalMesh>(nullptr, TEXT("/Script/Engine.SkeletalMesh'/Game/Asset/Character/Enemy/CavaliereAngelo/mesh/em5501.em5501'"));

	if (SKM)
	{
		GetMesh()->SetSkeletalMesh(SKM);

		Sword = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Sword"));

		Sword->SetupAttachment(GetMesh(), TEXT("R_WeaponHand"));

		CollisionArray.SetNum(static_cast<uint8>(EAngeloCollision::ALL));
		CollisionArray[static_cast<uint8>(EAngeloCollision::SWORD)] = Sword;
	}

	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -90.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	SetupFsm();

	AttackRange = 200.f;
	bCanPull = false;
}

void AAngelo::BeginPlay()
{
	Sword->OnComponentBeginOverlap.AddDynamic(this, &AAngelo::OverlapBegin);
	ToggleCollision(false, EAngeloCollision::ALL);
}

void AAngelo::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
}

void AAngelo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UE_LOG(LogTemp, Warning, TEXT("TickAngelo"));
	//UE_LOG(LogTemp, Warning, TEXT("%d"), FsmComp->GetCurrentState());
}

void AAngelo::ToggleCollision(bool Value, uint8 Where)
{
	ToggleCollision(Value, static_cast<EAngeloCollision>(Where));
}

void AAngelo::ToggleCollision(bool Value, EAngeloCollision Where)
{
	if (Where == EAngeloCollision::ALL)
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

void AAngelo::OverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
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

void AAngelo::SetupFsm()
{
	FsmComp = CreateDefaultSubobject<UFsmComponent>(TEXT("AngeloFsmComp"));
	FsmComp->SetIsReplicated(true);

	FsmComp->CreateState(EAngeloFsm::IDLE,
		//Start
		[this]()
		{
		},

		//Update
		[this](float DeltaTime)
		{
			if (TargetPlayer != nullptr)
			{
				FsmComp->ChangeState(EAngeloFsm::RUN);
				return;
			}
		},

		//End
		[this]()
		{
		}
	);

	FsmComp->CreateState(EAngeloFsm::RUN,
		//Start
		[this]()
		{
		},

		//Update
		[this](float DeltaTime)
		{
			auto Result = AiController->MoveToActor(TargetPlayer);

			if (FVector::Distance(GetActorLocation(), TargetPlayer->GetActorLocation()) <= AttackRange)
			{
				FsmComp->ChangeState(EAngeloFsm::ATTACK);
				return;
			}
		},

		//End
		[this]()
		{
		}
	);

	FsmComp->CreateState(EAngeloFsm::ATTACK,
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
					if (FVector::Distance(GetActorLocation(), TargetPlayer->GetActorLocation()) > AttackRange)
					{
						FsmComp->ChangeState(EAngeloFsm::RUN);
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

	FsmComp->CreateState(EAngeloFsm::DAMAGED,
		//Start
		[this]()
		{
		},

		//Update
		[this](float DeltaTime)
		{
			if (!GetMesh()->GetAnimInstance()->IsAnyMontagePlaying())
			{
				if (FVector::Distance(GetActorLocation(), TargetPlayer->GetActorLocation()) > AttackRange)
				{
					FsmComp->ChangeState(EAngeloFsm::RUN);
					return;
				}
				else
				{
					FsmComp->ChangeState(EAngeloFsm::ATTACK);
					return;
				}
			}
		},

		//End
		[this]()
		{
		}
	);

	FsmComp->CreateState(EAngeloFsm::DEAD,
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

	FsmComp->ChangeState(EAngeloFsm::IDLE);
}

void AAngelo::DamagedDefault()
{
	FsmComp->ChangeState(EAngeloFsm::DAMAGED);
}
