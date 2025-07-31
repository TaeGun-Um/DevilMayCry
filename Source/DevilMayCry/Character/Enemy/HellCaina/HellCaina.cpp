// Fill out your copyright notice in the Description page of Project Settings.


#include "HellCaina.h"


#include "Components/CapsuleComponent.h"
#include "Engine/DamageEvents.h" 
#include "../../Player/ParentCharacter.h"
#include "../../DamageType/GeneralDamageType.h"
#include "../../FsmComponent.h"
#include "AIController.h"

#include "GameFramework/Controller.h"
#include "../AI/EnemyController.h"

#include "DrawDebugHelpers.h"

AHellCaina::AHellCaina()
{
	//메시 세팅
	TObjectPtr<USkeletalMesh> SKM = LoadObject<USkeletalMesh>(nullptr, TEXT("/Script/Engine.SkeletalMesh'/Game/Asset/Character/Enemy/HellCaina/mesh/HellCainaFix.HellCainaFix'"));

	if (SKM)
	{
		GetMesh()->SetSkeletalMesh(SKM);

		Scythe = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Scythe"));
		Scythe->SetupAttachment(GetMesh(), "L_WeaponHand");
	}

	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -90.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 90.f));

	SetupFsm();

	AttackRange = 500.f;
}

void AHellCaina::BeginPlay()
{
	Super::BeginPlay();


	CollisionArray.SetNum(static_cast<uint8>(EHellCainaCollision::ALL));
	CollisionArray[static_cast<uint8>(EHellCainaCollision::SCYTHE)] = Scythe;

	Scythe->OnComponentBeginOverlap.AddDynamic(this, &AHellCaina::OverlapBegin);

	ToggleCollision(false, EHellCainaCollision::ALL);
}

void AHellCaina::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AHellCaina::ToggleCollision(bool Value, uint8 Where)
{
	ToggleCollision(Value, static_cast<EHellCainaCollision>(Where));
}

void AHellCaina::ToggleCollision(bool Value, EHellCainaCollision Where)
{
	if (Where == EHellCainaCollision::ALL)
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

void AHellCaina::OverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
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

void AHellCaina::SetupFsm()
{
	HellCainaFsmComp = CreateDefaultSubobject<UFsmComponent>(TEXT("HellCainaFsmComp"));
	HellCainaFsmComp->SetIsReplicated(true);

	HellCainaFsmComp->CreateState(EHellCainaFsm::IDLE,
		//Start
		[this]()
		{
		},

		//Update
		[this](float DeltaTime)
		{
			if (TargetPlayer != nullptr)
			{
				HellCainaFsmComp->ChangeState(EHellCainaFsm::WALK);
				return;
			}
		},

		//End
		[this]()
		{
		}
	);
	
	HellCainaFsmComp->CreateState(EHellCainaFsm::WALK,
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
				HellCainaFsmComp->ChangeState(EHellCainaFsm::ATTACK);
				return;
			}
		},

		//End
		[this]()
		{
		}
	);

	HellCainaFsmComp->CreateState(EHellCainaFsm::ATTACK,
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
					if (Dist > AttackRange)
					{
						HellCainaFsmComp->ChangeState(EHellCainaFsm::WALK);
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

	HellCainaFsmComp->CreateState(EHellCainaFsm::DAMAGED,
		//Start
		[this]()
		{
		},

		//Update
		[this](float DeltaTime)
		{
			if (bDead)
			{
				HellCainaFsmComp->ChangeState(EHellCainaFsm::DEAD);
				return;
			}

			if (!GetMesh()->GetAnimInstance()->IsAnyMontagePlaying())
			{

				float Dist = FVector::DistXY(GetActorLocation(), TargetPlayer->GetActorLocation());
				if (Dist > AttackRange)
				{
					HellCainaFsmComp->ChangeState(EHellCainaFsm::WALK);
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

	HellCainaFsmComp->CreateState(EHellCainaFsm::DEAD,
		//Start
		[this]()
		{
			DeadAnimation();
		},

		//Update
		[this](float DeltaTime)
		{
			if (!GetMesh()->GetAnimInstance()->IsAnyMontagePlaying())
			{
				Destroy();
				return;
			}
		},

		//End
		[this]()
		{
		}
	);

	HellCainaFsmComp->CreateState(EHellCainaFsm::END,
		//Start
		[this]()
		{
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


	HellCainaFsmComp->ChangeState(EHellCainaFsm::IDLE);
}

void AHellCaina::DamagedDefault()
{
	DamagedAnimation();
	HellCainaFsmComp->ChangeState(EHellCainaFsm::DAMAGED);
}

void AHellCaina::DamagedGeneral()
{
}

void AHellCaina::DamagedSnatch()
{
	//SnatchAnimation();
}

void AHellCaina::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

