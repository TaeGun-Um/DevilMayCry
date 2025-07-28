// Fill out your copyright notice in the Description page of Project Settings.


#include "Angelo.h"
#include "Components/CapsuleComponent.h"
#include "Engine/DamageEvents.h" 
#include "AIController.h"


#include "../../Player/ParentCharacter.h"
#include "../../DamageType/GeneralDamageType.h"
#include "../../DamageType/ImpulseDamageType.h"
#include "../../FsmComponent.h"
#include "../Attack/EnemyProjectile.h"
#include "../Attack/DelayDamage.h"

#include "Algo/RandomShuffle.h"

#include "Kismet/KismetMathLibrary.h"

#include "GameFramework/Controller.h"
#include "../AI/EnemyController.h"

#include "DrawDebugHelpers.h"

AAngelo::AAngelo()
{
	//메시 세팅
	TObjectPtr<USkeletalMesh> SKM = LoadObject<USkeletalMesh>(nullptr, TEXT("/Script/Engine.SkeletalMesh'/Game/Asset/Character/Enemy/CavaliereAngelo/mesh/em5501.em5501'"));

	if (SKM)
	{
		GetMesh()->SetSkeletalMesh(SKM);

		Sword = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Sword"));
		Sword->SetupAttachment(GetMesh(), "R_WeaponHand");
	}

	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -90.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	SetupFsm();

	bCanPull = false;
	AttackRange = 800.f;
	SetWalkSpeed(200.f);

	RakuraiPos.SetNum(RakuraiMaxCount);
}

void AAngelo::BeginPlay()
{
	Super::BeginPlay();

	Sword->OnComponentBeginOverlap.AddDynamic(this, &AAngelo::OverlapBegin);

	CollisionArray.SetNum(static_cast<uint8>(EAngeloCollision::ALL));
	CollisionArray[static_cast<uint8>(EAngeloCollision::SWORD)] = Sword;

	ToggleCollision(false, EAngeloCollision::ALL);

	FDelayDamageSetting Setter;
	Setter.Damage = 10.f;
	Setter.MaxDamageDelay = 1.5f;
	Setter.DamageType = UGeneralDamageType::StaticClass();
	Setter.IgnoreList.Add(this);
	Setter.Radius = 10.f;

	RakuraiPool.Reserve(RakuraiMaxCount);
	for (size_t i = 0; i < RakuraiMaxCount; i++)
	{
		RakuraiPool.Add(GetWorld()->SpawnActor<ADelayDamage>());
		RakuraiPool[i]->Setter = Setter;
	}
}

void AAngelo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
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
	if (bCanParry == true && SweepResult.Component->ComponentHasTag(Weapon))
	{
		AngeloFsmComp->ChangeState(EAngeloFsm::PARRY);
		return;
	}

	if (OtherActor && OtherActor != this)
	{
		if (AnimInst->Montage_GetCurrentSection() == Parry)
		{
			return;
		}
		TObjectPtr<AParentCharacter> Enemy = Cast<AParentCharacter>(SweepResult.GetActor());
		if (Enemy != nullptr)
		{
			FDamageEvent DamageEvent(UImpulseDamageType::StaticClass());
			Enemy->TakeDamage(AttackDamage, DamageEvent, GetController(), this);
		}
	}
}

void AAngelo::SetupFsm()
{
	AngeloFsmComp = CreateDefaultSubobject<UFsmComponent>(TEXT("AngeloFsmComp"));
	AngeloFsmComp->SetIsReplicated(true);

	AngeloFsmComp->CreateState(EAngeloFsm::IDLE,
		//Start
		[this]()
		{
		},

		//Update
		[this](float DeltaTime)
		{
			if (TargetPlayer != nullptr)
			{
				AngeloFsmComp->ChangeState(EAngeloFsm::RUN);
				return;
			}
		},

		//End
		[this]()
		{
		}
	);

	AngeloFsmComp->CreateState(EAngeloFsm::RUN,
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

			if (!AnimInst->IsAnyMontagePlaying())
			{
				int Random = FMath::RandRange(0, 5);
				if (Random)
				{
					AngeloFsmComp->ChangeState(EAngeloFsm::ATTACK);
					return;
				}
				else
				{
					AngeloFsmComp->ChangeState(EAngeloFsm::RAKURAI);
					return;
				}
			}

			if (FVector::DistXY(GetActorLocation(), TargetPlayer->GetActorLocation()) > DengekiStart)
			{
				AngeloFsmComp->ChangeState(EAngeloFsm::DENGEKI);
				return;
			}

			if (FVector::DistXY(GetActorLocation(), TargetPlayer->GetActorLocation()) <= AttackRange)
			{
				AnimInst->Montage_Stop(0.25f);
				return;
			}
		},

		//End
		[this]()
		{
		}
	);

	AngeloFsmComp->CreateState(EAngeloFsm::ATTACK,
		//Start
		[this]()
		{
			if (AnimInst->Montage_GetCurrentSection() != Parry)
			{
				AttackAnimation();
			}
		},

		//Update
		[this](float DeltaTime)
		{
			TurnToActor(DeltaTime);

			if (!AnimInst->IsAnyMontagePlaying())
			{
				if (FVector::DistXY(GetActorLocation(), TargetPlayer->GetActorLocation()) > AttackRange)
				{
					AngeloFsmComp->ChangeState(EAngeloFsm::RUN);
					return;
				}
				else
				{
					AttackAnimation();
				}
			}
		},

		//End
		[this]()
		{
		}
	);

	AngeloFsmComp->CreateState(EAngeloFsm::DAMAGED,
		//Start
		[this]()
		{
		},

		//Update
		[this](float DeltaTime)
		{
			if (bDead)
			{
				AngeloFsmComp->ChangeState(EAngeloFsm::DEAD);
				return;
			}

			if (!GetMesh()->GetAnimInstance()->IsAnyMontagePlaying())
			{
				if (FVector::DistXY(GetActorLocation(), TargetPlayer->GetActorLocation()) > AttackRange)
				{
					AngeloFsmComp->ChangeState(EAngeloFsm::RUN);
					return;
				}
				else
				{
					AngeloFsmComp->ChangeState(EAngeloFsm::ATTACK);
					return;
				}
			}
		},

		//End
		[this]()
		{
		}
	);

	AngeloFsmComp->CreateState(EAngeloFsm::PARRY,
		//Start
		[this]()
		{
			++CurParryCount;
			PrevSection = AnimInst->Montage_GetCurrentSection();
			AnimInst->Montage_JumpToSection(Parry);
			bCanParry = false;
			ToggleCollision(false, EAngeloCollision::ALL);
		},

		//Update
		[this](float DeltaTime)
		{
			if (CurParryCount == ParryToStunCount)
			{
				CurParryCount = 0;
				AngeloFsmComp->ChangeState(EAngeloFsm::STUN);
				return;
			}
			else
			{
				AngeloFsmComp->ChangeState(EAngeloFsm::ATTACK);
				return;
			}
		},

		//End
		[this]()
		{
		}
	);


	AngeloFsmComp->CreateState(EAngeloFsm::DENGEKI,
		//Start
		[this]()
		{
			DengekiAnimation();
			CurDengekiDelay = 0.f;
		},

		//Update
		[this](float DeltaTime)
		{
			TurnToActor(DeltaTime);

			if (!AnimInst->IsAnyMontagePlaying())
			{
				AngeloFsmComp->ChangeState(EAngeloFsm::RUN);
				return;
			}

			if (AnimInst->Montage_GetCurrentSection() == Loop)
			{
				FireDengeki(DeltaTime);
			}

			if (AnimInst->Montage_GetCurrentSection() != End &&
				FVector::DistXY(GetActorLocation(), TargetPlayer->GetActorLocation()) < DengekiEnd)
			{
				AnimInst->Montage_JumpToSection(End);
			}
		},

		//End
		[this]()
		{
		}
	);


	AngeloFsmComp->CreateState(EAngeloFsm::RAKURAI,
		//Start
		[this]()
		{
			RakuraiAnimation();
			CurRakuraiDelay = 0.f;
			RakuraiIndex = 0;
		},

		//Update
		[this](float DeltaTime)
		{
			TurnToActor(DeltaTime);

			if (AnimInst->Montage_GetCurrentSection() == Loop)
			{
				FireRakurai(DeltaTime);
			}

			if (!AnimInst->IsAnyMontagePlaying())
			{
				AngeloFsmComp->ChangeState(EAngeloFsm::IDLE);
				return;
			}
		},

		//End
		[this]()
		{
		}
	);

	AngeloFsmComp->CreateState(EAngeloFsm::WARP,
		//Start
		[this]()
		{
			WarpAnimation();
			WarpHP = CurHP;
		},

		//Update
		[this](float DeltaTime)
		{
			if (AnimInst->Montage_GetCurrentSection() == Loop)
			{
				if (CurHP<=WarpHP*WarpHPRatio)
				{
					AngeloFsmComp->ChangeState(EAngeloFsm::STUN);
					return;
				}
			}
			if (!AnimInst->IsAnyMontagePlaying())
			{
				AngeloFsmComp->ChangeState(EAngeloFsm::IDLE);
				return;
			}
		},

		//End
		[this]()
		{
		}
	);

	AngeloFsmComp->CreateState(EAngeloFsm::STUN,
		//Start
		[this]()
		{
			StunAnimation();
		},

		//Update
		[this](float DeltaTime)
		{
			if (!AnimInst->IsAnyMontagePlaying())
			{
				AngeloFsmComp->ChangeState(EAngeloFsm::IDLE);
				return;
			}
		},

		//End
		[this]()
		{
		}
	);

	AngeloFsmComp->CreateState(EAngeloFsm::DEAD,
		//Start
		[this]()
		{
			DeadAnimation();
		},

		//Update
		[this](float DeltaTime)
		{
			if (!AnimInst->IsAnyMontagePlaying())
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

	AngeloFsmComp->ChangeState(EAngeloFsm::IDLE);
}

void AAngelo::BlueprintChangeState(EAngeloFsm State)
{
	AngeloFsmComp->ChangeState(State);
}

void AAngelo::FireDengeki(float DeltaTime)
{
	CurDengekiDelay -= DeltaTime;

	if (CurDengekiDelay <= 0.f)
	{
		FVector SocketPos = GetMesh()->GetSocketLocation(L_WeaponHand);
		FVector TargetPos = TargetPlayer->GetActorLocation();

		TObjectPtr<AEnemyProjectile> Dengeki = GetWorld()->SpawnActor<AEnemyProjectile>(SocketPos, FRotator::ZeroRotator);

		FVector Dir = TargetPos - SocketPos;
		Dir.Normalize();
		Dengeki->Fire(Dir);

		CurDengekiDelay += MaxDengekiDelay;
	}
}

void AAngelo::InitRakurai()
{
	FVector Center = GetActorLocation();

	for (size_t i = 0; i < RakuraiMaxCount - 1; i++)
	{
		FVector2D Rand2D = FMath::RandPointInCircle(RakuraiRadius);

		RakuraiPos[i] = FVector(Center.X + Rand2D.X, Center.Y + Rand2D.Y, Center.Z + 100.f);
	}

	RakuraiPos[RakuraiMaxCount - 1] = TargetPlayer->GetActorLocation();
	RakuraiPos[RakuraiMaxCount - 1].Z = Center.Z + 100.f;


	Algo::RandomShuffle(RakuraiPos);
}

void AAngelo::FireRakurai(float DeltaTime)
{
	CurRakuraiDelay -= DeltaTime;

	while (RakuraiIndex < RakuraiMaxCount && CurRakuraiDelay <= 0.f)
	{
		FVector AttackPos = RakuraiPos[RakuraiIndex];
		FVector EndPos = AttackPos - FVector(0.f, 0.f, 1000.f);

		FHitResult Hit;

		FCollisionQueryParams Params;
		Params.bTraceComplex = false;
		Params.AddIgnoredActor(this);
		Params.AddIgnoredActor(TargetPlayer);

		// WorldStatic(구조물) 레이캐스트
		bool bHit = GetWorld()->LineTraceSingleByChannel(Hit, AttackPos, EndPos, ECC_WorldStatic, Params);

		DrawDebugLine(GetWorld(), AttackPos, EndPos, FColor::Green, false, 1.f, 0, 1.f);

		if (bHit)
		{
			//생성해둔 데미지 풀에 포지션 전달하고 on
			RakuraiPool[RakuraiIndex]->SetPos(Hit.ImpactPoint);
			RakuraiPool[RakuraiIndex]->ActiveSwitch(true);
		}


		CurRakuraiDelay += MaxRakuraiDelay;
		++RakuraiIndex;
	}
}

void AAngelo::DamagedDefault()
{
	if (CurHP <= MaxHP * WarpHPRatio && bWarpDone == false)
	{
		AngeloFsmComp->ChangeState(EAngeloFsm::WARP);
		bWarpDone = true;
		return;
	}

	if (AngeloFsmComp->GetCurrentState() == static_cast<uint8>(EAngeloFsm::ATTACK)
		|| AngeloFsmComp->GetCurrentState() == static_cast<uint8>(EAngeloFsm::DENGEKI)
		|| AngeloFsmComp->GetCurrentState() == static_cast<uint8>(EAngeloFsm::WARP))
	{
		return;
	}


	AngeloFsmComp->ChangeState(EAngeloFsm::DAMAGED);

	DamagedAnimation();
}

void AAngelo::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
