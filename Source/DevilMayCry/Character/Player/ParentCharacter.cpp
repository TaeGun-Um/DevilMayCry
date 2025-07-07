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
	TurnToEnemy(DeltaTime);
}

// Called to bind functionality to input
//void AParentCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
//{
//	Super::SetupPlayerInputComponent(PlayerInputComponent);
//}

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

void AParentCharacter::TurnToEnemy(float DeltaTime)
{
	if (IsValid(LockOnEnemy.GetClass()))
	{
		FVector Direction = LockOnEnemy->GetActorLocation() - GetActorLocation();

		//서치 범위 벗어나면 종료
		if (Direction.Length() > SearchRadius)
		{
			LockOff();
			return;
		}

		//액터 방향 돌리기
		FRotator SmoothRot = FMath::RInterpTo(GetActorForwardVector().Rotation(), Direction.Rotation().GetNormalized(), DeltaTime, LockOnRatio);
		SmoothRot.Roll = 0.f;
		SmoothRot.Pitch = 0.f;

		SetActorRotation(SmoothRot);


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
	else
	{
		if (SpringArmComp->GetRelativeLocation() != FVector::ZeroVector)
		{
			FVector DestVector = FMath::VInterpTo(SpringArmComp->GetRelativeLocation(), FVector::ZeroVector, DeltaTime, LockOnRatio);

			SpringArmComp->SetRelativeLocation(DestVector);

			float ArmLength = FMath::FInterpTo(SpringArmComp->TargetArmLength, CameraArmLength, DeltaTime, LockOnRatio);
			SpringArmComp->TargetArmLength = ArmLength;
		}
	}
}

void AParentCharacter::LockOn()
{
	if (LockOnEnemy == nullptr)
	{
		EnemyCheck();
	}

	if (EnemyCameraCheck()) // true면 벽이 있음
	{
		LockOnEnemy = nullptr;
	}
}

void AParentCharacter::LockOff()
{
	LockOnEnemy = nullptr;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
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
	MoveDir = FVector2D(DirX+DirY);
	MoveDir.Normalize();

	if (FsmComp->GetCurrentState() != static_cast<int32>(EPlayerState::IDLE))
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

void AParentCharacter::RightClick()
{
}

void AParentCharacter::WheelClick()
{
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
	LockOn();
}

void AParentCharacter::Server_ShiftKeyComplete_Implementation()
{
	Multicast_ShiftKeyComplete();
}

void AParentCharacter::Multicast_ShiftKeyComplete_Implementation()
{
	bLockOnKey = false;
	LockOff();
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

void AParentCharacter::DefaultEvade()
{
}

void AParentCharacter::DefaultAttack()
{
}

void AParentCharacter::DefaultJump(float JumpHeight, FVector2D Dir)
{
}

void AParentCharacter::DefaultZKey()
{
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
