// Fill out your copyright notice in the Description page of Project Settings.


#include "ParentCharacter.h"
#include "FsmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"



void AParentCharacter::SetupFsm()
{
	FsmComp = CreateDefaultSubobject<UFsmComponent>(TEXT("FsmComp"));
	//FsmComp->RegisterComponent();
	FsmComp->SetIsReplicated(true);

	FsmComp->CreateState(EPlayerState::IDLE,
		//Start
		[this]()
		{
		},

		//Update
		[this](float DeltaTime)
		{
			if (bAttackKey == true)
			{
				DefaultAttack();
			}

			if (bLockOnKey == true)
			{
				FsmComp->ChangeState(EPlayerState::LOCKON);
				return;
			}

			if (MoveDir != FVector2D::ZeroVector)
			{
				FsmComp->ChangeState(EPlayerState::RUN);
				return;
			}

			if (GetCharacterMovement()->IsFalling())
			{
				FsmComp->ChangeState(EPlayerState::FALL);
				return;
			}

			if (bJumpKey == true)
			{
				FsmComp->ChangeState(EPlayerState::JUMP);
				return;
			}
		},

		//End
		[this]()
		{
		}
	);

	FsmComp->CreateState(EPlayerState::RUN,
		//Start
		[this]()
		{
		},

		//Update
		[this](float DeltaTime)
		{
			if (bAttackKey == true)
			{
				DefaultAttack();
			}

			if (GetCharacterMovement()->IsFalling())
			{
				FsmComp->ChangeState(EPlayerState::FALL);
				return;
			}

			if (bLockOnKey == true)
			{
				FsmComp->ChangeState(EPlayerState::LOCKON);
				return;
			}

			if (bJumpKey == true)
			{
				FsmComp->ChangeState(EPlayerState::JUMP);
				return;
			}

			if (MoveDir == FVector2D::ZeroVector)
			{
				FsmComp->ChangeState(EPlayerState::IDLE);
				return;
			}


		},

		//End
		[this]()
		{
		}
	);

	FsmComp->CreateState(EPlayerState::JUMP,
		//Start
		[this]()
		{
			JumpRatio = 0.f;
			JumpStartPos = GetActorLocation();
			JumpEndPos = CheckJumpPos(MaxJumpHeight);
			LaunchCharacter(FVector(0.f, 0.f, 100.f), false, true);
		},
		//Update
		[this](float DeltaTime)
		{
			if (bAttackKey == true)
			{
				DefaultAttack();
			}

			JumpRatio += DeltaTime * 3.f;
			SetActorLocation(FMath::LerpStable(JumpStartPos, JumpEndPos, JumpRatio));

			if (GetActorLocation().Z >= JumpEndPos.Z)
			{
				FsmComp->ChangeState(EPlayerState::FALL);
				return;
			}

			if (!GetCharacterMovement()->IsFalling())
			{
				FsmComp->ChangeState(EPlayerState::IDLE);
				return;
			}
		},
		//End
		[this]()
		{
			JumpRatio = 0.f;
		}
	);

	FsmComp->CreateState(EPlayerState::FALL,
		//Start
		[this]()
		{
		},
		//Update
		[this](float DeltaTime)
		{
			if (bAttackKey == true)
			{
				DefaultAttack();
			}

			if (!GetCharacterMovement()->IsFalling())
			{
				FsmComp->ChangeState(EPlayerState::IDLE);
				return;
			}
		},
		//End
		[this]()
		{
		}
	);

	FsmComp->CreateState(EPlayerState::ATTACK,
		//Start
		[this]()
		{
		},
		//Update
		[this](float DeltaTime)
		{
			TWeakObjectPtr<UAnimInstance> AnimIns = Cast<UAnimInstance>(GetMesh()->GetAnimInstance());
			if (AnimIns.Get() && !AnimIns->IsAnyMontagePlaying())
			{
				if (bLockOnKey)
				{
					FsmComp->ChangeState(EPlayerState::LOCKON);
				}
				else
				{
					FsmComp->ChangeState(EPlayerState::IDLE);
				}
			}
		},
		//End
		[this]()
		{
		}
	);

	FsmComp->CreateState(EPlayerState::EVADE,
		//Start
		[this]()
		{
			bPrevEvade = true;
		},
		//Update
		[this](float DeltaTime)
		{
			TWeakObjectPtr<UAnimInstance> AnimIns = Cast<UAnimInstance>(GetMesh()->GetAnimInstance());
			if (AnimIns.Get() && !AnimIns->IsAnyMontagePlaying())
			{
				if (bLockOnKey)
				{
					FsmComp->ChangeState(EPlayerState::LOCKON);
				}
				else
				{
					FsmComp->ChangeState(EPlayerState::IDLE);
				}
			}
		},
		//End
		[this]()
		{
		}
	);

	FsmComp->CreateState(EPlayerState::LOCKON,
		//Start
		[this]()
		{
		},
		//Update
		[this](float DeltaTime)
		{
			if (bAttackKey == true)
			{
				DefaultAttack();
			}

			if (bLockOnKey == false)
			{
				FsmComp->ChangeState(EPlayerState::IDLE);
			}

			if (bJumpKey)
			{
				DefaultEvade();
			}
		},
		//End
		[this]()
		{
			bPrevEvade = false;
		}
	);

	FsmComp->CreateState(EPlayerState::JUMPBACK,
		//Start
		[this]()
		{
			JumpRatio = 0.f;
			JumpStartPos = GetActorLocation();
			JumpEndPos = CheckJumpPos(MaxJumpHeight * 2.f);

			JumpBackPos = JumpStartPos + FVector(MoveDir.X * JumpBackDistance, MoveDir.Y * JumpBackDistance, 0.f);
			JumpBackMiddlePos = JumpStartPos + JumpBackPos;
			JumpBackMiddlePos /= 2.f;
			JumpBackMiddlePos.Z = JumpEndPos.Z;

			LaunchCharacter(FVector(0.f, 0.f, 100.f), false, true);
		},
		//Update
		[this](float DeltaTime)
		{
			JumpRatio += DeltaTime * 1.f;

			FVector A = FMath::LerpStable(JumpStartPos, JumpBackMiddlePos, JumpRatio);
			FVector B = FMath::LerpStable(JumpBackMiddlePos, JumpBackPos, JumpRatio);
			FVector ResultPos = FMath::LerpStable(A, B, JumpRatio);

			SetActorLocation(ResultPos);

			TWeakObjectPtr<UAnimInstance> AnimIns = Cast<UAnimInstance>(GetMesh()->GetAnimInstance());
			if (AnimIns.Get() && !AnimIns->IsAnyMontagePlaying())
			{
				if (GetCharacterMovement()->IsFalling())
				{
					FsmComp->ChangeState(EPlayerState::FALL);
					return;
				}
			}

			if (!GetCharacterMovement()->IsFalling())
			{

				FsmComp->ChangeState(EPlayerState::IDLE);

			}
		},
		//End
		[this]()
		{
		}
	);

	FsmComp->CreateState(EPlayerState::COMBOCHECK,
		//Start
		[this]()
		{
		},
		//Update
		[this](float DeltaTime)
		{
			if (bAttackKey == true)
			{
				DefaultAttack();
			}

			TWeakObjectPtr<UAnimInstance> AnimIns = Cast<UAnimInstance>(GetMesh()->GetAnimInstance());
			if (AnimIns.Get() && !AnimIns->IsAnyMontagePlaying())
			{
				FsmComp->ChangeState(EPlayerState::IDLE);
				return;
			}
		},
		//End
		[this]()
		{
		}
	);

	FsmComp->ChangeState(EPlayerState::IDLE);
}

FVector AParentCharacter::CheckJumpPos(float Height)
{
	FHitResult Result;


	bool bHit = GetWorld()->LineTraceSingleByObjectType(Result, JumpStartPos, JumpStartPos + FVector(0.f, 0.f, Height), CheckParam);

	if (bHit)
	{
		return Result.ImpactPoint;
	}
	else
	{
		return JumpStartPos + FVector(0.f, 0.f, Height);
	}
}

void AParentCharacter::BlueprintChangeState(EPlayerState Value)
{
	FsmComp->ChangeState(Value);
}

EPlayerState AParentCharacter::BlueprintGetCurState()
{
	return EPlayerState(FsmComp->GetCurrentState());
}
