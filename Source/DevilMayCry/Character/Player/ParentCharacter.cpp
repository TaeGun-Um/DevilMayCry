// Fill out your copyright notice in the Description page of Project Settings.


#include "ParentCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Net/UnrealNetwork.h"

#include "../Enemy/EnemyBase.h"
#include "../FsmComponent.h"


#include "DrawDebugHelpers.h"

// Sets default values
AParentCharacter::AParentCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -90.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	CameraInit();

	SetupFsm();

	CheckParam.AddObjectTypesToQuery(ECC_WorldStatic);
	CheckParam.AddObjectTypesToQuery(ECC_WorldDynamic);

	Tags.Add(TEXT("Player"));
}

// Called when the game starts or when spawned
void AParentCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AParentCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (LockOnEnemy == nullptr)
	{
		EnemyCheck();
	}

	ResetCamera(GetWorld()->DeltaTimeSeconds);
}

// Called to bind functionality to input
//void AParentCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
//{
//	Super::SetupPlayerInputComponent(PlayerInputComponent);
//}


void AParentCharacter::ResetCamera(float DeltaTime)
{
	if (!bLockOnKey && SpringArmComp->GetRelativeLocation() != FVector::ZeroVector)
	{
		FVector DestVector = FMath::VInterpTo(SpringArmComp->GetRelativeLocation(), FVector::ZeroVector, DeltaTime, LockOnRatio);

		SpringArmComp->SetRelativeLocation(DestVector);

		float ArmLength = FMath::FInterpTo(SpringArmComp->TargetArmLength, CameraArmLength, DeltaTime, LockOnRatio);
		SpringArmComp->TargetArmLength = ArmLength;
	}
}

void AParentCharacter::CameraInit()
{
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->TargetArmLength = CameraArmLength;
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->bDoCollisionTest = true;
	SpringArmComp->ProbeChannel = ECC_Camera;
	SpringArmComp->ProbeSize = 8.0f;

	SpringArmComp->bEnableCameraRotationLag = true;
	SpringArmComp->CameraRotationLagSpeed = 10.f;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CharacterCamera"));
	CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);
	CameraComp->bUsePawnControlRotation = false;


	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 540.f, 0.f);
}

void AParentCharacter::CenterCamera(float DeltaTime)
{
	if (LockOnEnemy != nullptr)
	{
		FVector Direction = LockOnEnemy->GetActorLocation() - GetActorLocation();

		//카메라 중심점 변경
		FVector CenterPos = (LockOnEnemy->GetActorLocation() + GetActorLocation()) * 0.5f;

		FVector DestVector = FMath::VInterpTo(SpringArmComp->GetComponentLocation(), CenterPos, DeltaTime, LockOnRatio);

		SpringArmComp->SetWorldLocation(DestVector);

		//거리 비례 카메라암
		if (Direction.Length() > CameraArmLength)
		{

			float AddLength = FMath::GetMappedRangeValueClamped(
				FVector2D(CameraArmLength, SearchRadius),       // 비교 값
				FVector2D(0.f, CameraArmLength),                // 압축 값
				Direction.Length()                              // 넣을 값
			);
			SpringArmComp->TargetArmLength = CameraArmLength + AddLength;
		}

		//ui 만들어지기 전까지 사용할 락온 디버깅용 구체
		DrawDebugSphere(GetWorld(), LockOnEnemy->GetActorLocation(), 30.f, 12, FColor::Red);
	}
}


void AParentCharacter::TurnToEnemy(float DeltaTime)
{
	if (LockOnEnemy != nullptr)
	{
		FVector Direction = LockOnEnemy->GetActorLocation() - GetActorLocation();

		//서치 범위 벗어나면 종료
		if (Direction.Length() > SearchRadius)
		{
			SetStrafe(false);
			return;
		}

		//액터 방향 돌리기
		FRotator SmoothRot = FMath::RInterpTo(GetActorForwardVector().Rotation(), Direction.Rotation().GetNormalized(), DeltaTime, LockOnRatio);
		SmoothRot.Roll = 0.f;
		SmoothRot.Pitch = 0.f;

		SetActorRotation(SmoothRot);
		//SetActorRotation(Direction.Rotation().GetNormalized());
	}
}

void AParentCharacter::LockOn(float DeltaTime)
{
	if (EnemyCameraCheck()) // true면 벽이 있음
	{
		LockOnEnemy = nullptr;
	}
	TurnToEnemy(DeltaTime);
	CenterCamera(DeltaTime);
}

void AParentCharacter::SetStrafe(bool Value)
{
	GetCharacterMovement()->bOrientRotationToMovement = !Value;

	if (Value)
	{
		GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
	}
}

void AParentCharacter::Server_SetKeyDir_Implementation(const FVector2D& Value)
{
	Multicast_SetKeyDir(Value);
}

void AParentCharacter::Multicast_SetKeyDir_Implementation(const FVector2D& Value)
{
	KeyDir = Value;
	KeyDir.Normalize();
}

void AParentCharacter::Server_MoveKey_Implementation(const FVector2D& Value)
{
	Multicast_MoveKey(Value);
}
void AParentCharacter::Multicast_MoveKey_Implementation(const FVector2D& Value)
{
	//FVector DirX = GetActorRotation().Vector().ForwardVector * GetVelocity().X;
	//FVector DirY = GetActorRotation().Vector().RightVector * GetVelocity().Y;
	//MoveDir = FVector2D(DirX+DirY);
	//MoveDir.Normalize();



	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	const FVector ForwardVector = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightVector = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	FVector DirX = ForwardVector * Value.X;
	FVector DirY = RightVector * Value.Y;
	MoveDir = FVector2D(DirX + DirY);
	MoveDir.Normalize();

	if (bMoveOk/*FsmComp->GetCurrentState() != static_cast<int32>(EPlayerState::IDLE)*/)
	{
		AddMovementInput(ForwardVector, Value.X);
		AddMovementInput(RightVector, Value.Y);
	}
}

void AParentCharacter::Server_MoveComplete_Implementation()
{
	Multicast_MoveComplete();
}
void AParentCharacter::Multicast_MoveComplete_Implementation()
{
	MoveDir = FVector2D::ZeroVector;
	KeyDir = FVector2D::ZeroVector;
}

void AParentCharacter::Server_WheelClickStart_Implementation()
{
	Multicast_WheelClickStart();
}

void AParentCharacter::Multicast_WheelClickStart_Implementation()
{
	bWheelClick = true;
}

void AParentCharacter::Server_WheelClickComplete_Implementation()
{
	Multicast_WheelClickComplete();
}

void AParentCharacter::Multicast_WheelClickComplete_Implementation()
{
	bWheelClick = false;
}

void AParentCharacter::EKey()
{
}

void AParentCharacter::Server_ShiftKeyStart_Implementation()
{
	Multicast_ShiftKeyStart();
}

void AParentCharacter::Multicast_ShiftKeyStart_Implementation()
{
	SetStrafe(true);
	bLockOnKey = true;
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	GetCharacterMovement()->bOrientRotationToMovement = false;
}

void AParentCharacter::Server_ShiftKey_Implementation()
{
	Multicast_ShiftKey();
}

void AParentCharacter::Multicast_ShiftKey_Implementation()
{
	LockOn(GetWorld()->DeltaTimeSeconds);

	CenterCamera(GetWorld()->DeltaTimeSeconds);
}

void AParentCharacter::Server_ShiftKeyComplete_Implementation()
{
	Multicast_ShiftKeyComplete();
}

void AParentCharacter::Multicast_ShiftKeyComplete_Implementation()
{
	bLockOnKey = false;
	SetStrafe(false);
}

void AParentCharacter::Server_SpaceKeyComplete_Implementation()
{
	Multicast_SpaceKeyComplete();
}

void AParentCharacter::Multicast_SpaceKeyComplete_Implementation()
{
	bJumpKey = false;
}
void AParentCharacter::Server_SpaceKeyStart_Implementation()
{
	Multicast_SpaceKeyStart();
}

void AParentCharacter::Multicast_SpaceKeyStart_Implementation()
{
	bJumpKey = true;
}

void AParentCharacter::Server_ZKeyStart_Implementation()
{
	Multicast_ZKeyStart();
}

void AParentCharacter::Multicast_ZKeyStart_Implementation()
{
	bZKey = true;
}

void AParentCharacter::Server_RightClickStart_Implementation()
{
	Multicast_RightClickStart();
}

void AParentCharacter::Multicast_RightClickStart_Implementation()
{
	bRightClick = true;
}

void AParentCharacter::Server_RightClickComplete_Implementation()
{
	Multicast_RightClickComplete();
}

void AParentCharacter::Multicast_RightClickComplete_Implementation()
{
	bRightClick = false;
}

void AParentCharacter::LockOnEvade()
{

}

void AParentCharacter::Attack()
{
}

void AParentCharacter::Jumping(float JumpHeight, FVector2D Dir, bool bBack)
{
}

void AParentCharacter::ZKeyStart()
{
}

void AParentCharacter::ZKeyEnd()
{
}

void AParentCharacter::RightClick()
{
}

void AParentCharacter::Shift_WheelClick()
{
}

void AParentCharacter::WheelClick()
{
}

void AParentCharacter::WallCheck()
{
	if (EnemyCameraCheck())
	{
		LockOnEnemy = nullptr;
	}
}


void AParentCharacter::Server_LeftClickStart_Implementation()
{
	Multicast_LeftClickStart();
}

void AParentCharacter::Multicast_LeftClickStart_Implementation()
{
	bAttackKey = true;
}

void AParentCharacter::Server_LeftClickComplete_Implementation()
{
	Multicast_LeftClickComplete();
}

void AParentCharacter::Multicast_LeftClickComplete_Implementation()
{
	bAttackKey = false;
}

void AParentCharacter::Server_ZKeyComplete_Implementation()
{
	Multicast_ZKeyComplete();
}

void AParentCharacter::Multicast_ZKeyComplete_Implementation()
{
	bZKey = false;
}
