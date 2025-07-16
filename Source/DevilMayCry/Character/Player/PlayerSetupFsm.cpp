// Fill out your copyright notice in the Description page of Project Settings.


#include "ParentCharacter.h"
#include "../FsmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "../Enemy/EnemyBase.h"



void AParentCharacter::SetupFsm()
{
	FsmComp = CreateDefaultSubobject<UFsmComponent>(TEXT("FsmComp"));
	//FsmComp->RegisterComponent();
	FsmComp->SetIsReplicated(true);

	FsmComp->CreateState(EPlayerState::IDLE,
		//Start
		[this]()
		{
			SetStrafe(false);
			bMoveOk = true;
			CurComboCount = 0;
		},

		//Update
		[this](float DeltaTime)
		{
			if (bLockOnKey && bWheelClick)
			{
				FsmComp->ChangeState(EPlayerState::SHIFTWHEELCLICK);
				return;
			}
			if (!bLockOnKey && bWheelClick)
			{
				FsmComp->ChangeState(EPlayerState::WHEELCLICK);
				return;
			}

			if (bZKey == true)
			{
				FsmComp->ChangeState(EPlayerState::Z_ACTION);
				return;
			}

			if (bAttackKey == true)
			{
				Attack();
				return;
			}

			if (bRightClick == true)
			{
				FsmComp->ChangeState(EPlayerState::R_CLICK);
				return;
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
			bMoveOk = true;
		},

		//Update
		[this](float DeltaTime)
		{
			if (bLockOnKey && bWheelClick)
			{
				FsmComp->ChangeState(EPlayerState::SHIFTWHEELCLICK);
				return;
			}
			if (!bLockOnKey && bWheelClick)
			{
				FsmComp->ChangeState(EPlayerState::WHEELCLICK);
				return;
			}
			if (bZKey == true)
			{
				FsmComp->ChangeState(EPlayerState::Z_ACTION);
				return;
			}


			if (bAttackKey == true)
			{
				Attack();
				return;
			}

			if (bRightClick == true)
			{
				FsmComp->ChangeState(EPlayerState::R_CLICK);
				return;
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
			Jumping(MaxJumpHeight, MoveDir);
		},
		//Update
		[this](float DeltaTime)
		{
			if (bLockOnKey && bWheelClick)
			{
				FsmComp->ChangeState(EPlayerState::SHIFTWHEELCLICK);
				return;
			}
			if (!bLockOnKey && bWheelClick)
			{
				FsmComp->ChangeState(EPlayerState::WHEELCLICK);
				return;
			}
			if (bZKey == true)
			{
				FsmComp->ChangeState(EPlayerState::Z_ACTION);
				return;
			}


			if (bAttackKey == true)
			{
				Attack();
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
		}
	);

	FsmComp->CreateState(EPlayerState::FALL,
		//Start
		[this]()
		{
			GetCharacterMovement()->GravityScale = 5.f;
		},
		//Update
		[this](float DeltaTime)
		{
			if (bLockOnKey && bWheelClick)
			{
				FsmComp->ChangeState(EPlayerState::SHIFTWHEELCLICK);
				return;
			}
			if (!bLockOnKey && bWheelClick)
			{
				FsmComp->ChangeState(EPlayerState::WHEELCLICK);
				return;
			}
			if (bZKey == true)
			{
				FsmComp->ChangeState(EPlayerState::Z_ACTION);
				return;
			}


			if (bAttackKey == true)
			{
				Attack();
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
			bMoveOk = true;
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
			TObjectPtr<UAnimInstance> AnimIns = Cast<UAnimInstance>(GetMesh()->GetAnimInstance());
			if (bMoveOk || AnimIns.Get() && !AnimIns->IsAnyMontagePlaying())
			{
				if (bLockOnKey && bWheelClick)
				{
					FsmComp->ChangeState(EPlayerState::SHIFTWHEELCLICK);
					return;
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
			TObjectPtr<UAnimInstance> AnimIns = Cast<UAnimInstance>(GetMesh()->GetAnimInstance());
			if (AnimIns.Get() && !AnimIns->IsAnyMontagePlaying())
			{
				if (bLockOnKey && bWheelClick)
				{
					FsmComp->ChangeState(EPlayerState::SHIFTWHEELCLICK);
					return;
				}

				if (bLockOnKey)
				{
					FsmComp->ChangeState(EPlayerState::LOCKON);
					return;
				}
				else
				{
					FsmComp->ChangeState(EPlayerState::IDLE);
					return;
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
			SetStrafe(true);
		},
		//Update
		[this](float DeltaTime)
		{
			if (bWheelClick)
			{
				FsmComp->ChangeState(EPlayerState::SHIFTWHEELCLICK);
				return;
			}

			if (bAttackKey == true)
			{
				Attack();
				return;
			}
			if (bZKey == true)
			{
				FsmComp->ChangeState(EPlayerState::Z_ACTION);
				return;
			}

			if (bRightClick == true)
			{
				FsmComp->ChangeState(EPlayerState::R_CLICK);
				return;
			}

			if (bLockOnKey == false)
			{
				FsmComp->ChangeState(EPlayerState::IDLE);
				return;
			}

			if (bJumpKey)
			{
				LockOnEvade();
				return;
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
			Jumping(MaxJumpHeight, MoveDir, true);
		},
		//Update
		[this](float DeltaTime)
		{
			TObjectPtr<UAnimInstance> AnimIns = Cast<UAnimInstance>(GetMesh()->GetAnimInstance());
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
				if (AnimIns.Get() && AnimIns->IsAnyMontagePlaying())
				{
					AnimIns->StopAllMontages(0.1f);
				}

				FsmComp->ChangeState(EPlayerState::IDLE);
				return;
			}
		},
		//End
		[this]()
		{
			GetCharacterMovement()->GravityScale = 1.f;
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
				Attack();
				return;
			}

			TObjectPtr<UAnimInstance> AnimIns = Cast<UAnimInstance>(GetMesh()->GetAnimInstance());
			if (bMoveOk && MoveDir != FVector2D::ZeroVector)
			{
				if (AnimIns.Get() && AnimIns->IsAnyMontagePlaying())
				{
					AnimIns->StopAllMontages(0.25f);
					FsmComp->ChangeState(EPlayerState::IDLE);
					return;
				}
			}
			if (bLockOnKey)
			{
				FsmComp->ChangeState(EPlayerState::LOCKON);
				return;
			}
			if (AnimIns.Get() && !AnimIns->IsAnyMontagePlaying())
			{
				if (GetCharacterMovement()->IsFalling())
				{
					FsmComp->ChangeState(EPlayerState::FALL);
					return;
				}
				else
				{
					FsmComp->ChangeState(EPlayerState::IDLE);
					return;
				}
			}
		},
		//End
		[this]()
		{
		}
	);

	FsmComp->CreateState(EPlayerState::WHEELCLICK,
		//Start
		[this]()
		{
			bMoveOk = false;

			if (GetCharacterMovement()->IsFalling())
			{
				GetCharacterMovement()->GravityScale = 0.1f;
			}
		},
		//Update
		[this](float DeltaTime)
		{
			if (GetCharacterMovement()->IsFalling())
			{
				GetCharacterMovement()->Velocity = FVector::ZeroVector;
			}

			if (AnimEnd)
			{
				if (GetCharacterMovement()->IsFalling())
				{
					FsmComp->ChangeState(EPlayerState::FALL);
					return;
				}
				else
				{
					FsmComp->ChangeState(EPlayerState::IDLE);
					return;
				}
			}
		},
		//End
		[this]()
		{
			AnimEnd = false;
		}
	);

	FsmComp->CreateState(EPlayerState::R_CLICK,
		//Start
		[this]()
		{
			bMoveOk = true;
			SetStrafe(true);
		},
		//Update
		[this](float DeltaTime)
		{
			if (AnimEnd)
			{
				FsmComp->ChangeState(EPlayerState::R_CLICKDELAY);
				return;
			}

			if (LockOnEnemy != nullptr)
			{
				FVector Direction = LockOnEnemy->GetActorLocation() - GetActorLocation();

				//서치 범위 벗어나면 종료
				if (Direction.Length() > SearchRadius)
				{
					SetStrafe(false);
					return;
				}

				TurnToEnemy(DeltaTime);
			}
		},
		//End
		[this]()
		{

			AnimEnd = false;
		}
	);


	FsmComp->CreateState(EPlayerState::R_CLICKDELAY,
		//Start
		[this]()
		{
			bMoveOk = true;
			RightClickDelay = 0.f;
		},
		//Update
		[this](float DeltaTime)
		{
			RightClickDelay += DeltaTime;

			if (bLockOnKey && bWheelClick)
			{
				FsmComp->ChangeState(EPlayerState::SHIFTWHEELCLICK);
				return;
			}
			if (!bLockOnKey && bWheelClick)
			{
				FsmComp->ChangeState(EPlayerState::WHEELCLICK);
				return;
			}


			if (bRightClick)
			{
				FsmComp->ChangeState(EPlayerState::R_CLICK);
				return;
			}

			if (bJumpKey == true)
			{
				FsmComp->ChangeState(EPlayerState::JUMP);
				return;
			}

			if (bLockOnKey)
			{
				FsmComp->ChangeState(EPlayerState::LOCKON);
				bPrevEvade = true;
				return;
			}

			if (RightClickDelay >= 1.f)
			{
				FsmComp->ChangeState(EPlayerState::IDLE);
				return;
			}


			if (LockOnEnemy != nullptr)
			{
				FVector Direction = LockOnEnemy->GetActorLocation() - GetActorLocation();

				//서치 범위 벗어나면 종료
				if (Direction.Length() > SearchRadius)
				{
					SetStrafe(false);
					return;
				}

				TurnToEnemy(DeltaTime);
			}
		},
		//End
		[this]()
		{
			TObjectPtr<UAnimInstance> AnimIns = Cast<UAnimInstance>(GetMesh()->GetAnimInstance());
			if (AnimIns.Get() && AnimIns->IsAnyMontagePlaying())
			{
				AnimIns->StopAllMontages(0.25f);
			}

			ZKeyEnd();
		}
	);

	FsmComp->CreateState(EPlayerState::SHIFTWHEELCLICK,
		//Start
		[this]()
		{
			bMoveOk = false;
			WallCheck();

			Shift_WheelClick();

			if (GetCharacterMovement()->IsFalling())
			{
				GetCharacterMovement()->GravityScale = 0.1f;
			}
		},
		//Update
		[this](float DeltaTime)
		{
			if (GetCharacterMovement()->IsFalling())
			{
				GetCharacterMovement()->Velocity = FVector::ZeroVector;
			}

			if (AnimEnd)
			{
				if (GetCharacterMovement()->IsFalling())
				{
					FsmComp->ChangeState(EPlayerState::FALL);
					return;
				}
				else
				{
					FsmComp->ChangeState(EPlayerState::IDLE);
					return;
				}
			}
		},
		//End
		[this]()
		{
			AnimEnd = false;
			bMoveOk = true;
		}
	);

	FsmComp->CreateState(EPlayerState::Z_ACTION,
		//Start
		[this]()
		{
			bMoveOk = false;

			if (GetCharacterMovement()->IsFalling())
			{
				GetCharacterMovement()->GravityScale = 0.1f;
			}
		},
		//Update
		[this](float DeltaTime)
		{
			if (GetCharacterMovement()->IsFalling())
			{
				GetCharacterMovement()->Velocity = FVector::ZeroVector;
			}

			if (AnimEnd)
			{
				if (GetCharacterMovement()->IsFalling())
				{
					FsmComp->ChangeState(EPlayerState::FALL);
					return;
				}
				else
				{
					FsmComp->ChangeState(EPlayerState::IDLE);
					return;
				}
			}
		},
		//End
		[this]()
		{
			AnimEnd = false; 
			ZKeyEnd();
		}
	);


	FsmComp->ChangeState(EPlayerState::IDLE);
}

void AParentCharacter::BlueprintChangeState(EPlayerState Value)
{
	FsmComp->ChangeState(Value);
}

EPlayerState AParentCharacter::BlueprintGetCurState()
{
	return EPlayerState(FsmComp->GetCurrentState());
}
