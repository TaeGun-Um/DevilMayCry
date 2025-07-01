// Fill out your copyright notice in the Description page of Project Settings.


#include "ParentCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "../Enemy/EnemyBase.h"
#include "Kismet/KismetMathLibrary.h"

#include "Net/UnrealNetwork.h"


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
    StateChanger();
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
        
        //��ġ ���� ����� ����
        if (Direction.Length()>SearchRadius)
        {
            LockOff();
            return;
        }

        //���� ���� ������
        FRotator SmoothRot = FMath::RInterpTo(GetActorForwardVector().Rotation(), Direction.Rotation().GetNormalized(), DeltaTime, LockOnRatio);
        SmoothRot.Roll = 0.f;
		SmoothRot.Pitch = 0.f;

		SetActorRotation(SmoothRot); 
        

        //ī�޶� �߽��� ����
        FVector CenterPos = (LockOnEnemy->GetActorLocation() + GetActorLocation())*0.5f;

        FVector DestVector = FMath::VInterpTo(SpringArmComp->GetComponentLocation(), CenterPos, DeltaTime,LockOnRatio);

        SpringArmComp->SetWorldLocation(DestVector);

        //�Ÿ� ��� ī�޶��
        if (Direction.Length() > CameraArmLength)
        {

            float AddLength = FMath::GetMappedRangeValueClamped(
                FVector2D(CameraArmLength, SearchRadius),   // �� ��
                FVector2D(0.f, CameraArmLength),       // ���� ��
                Direction.Length()                          // ���� ��
            );
            SpringArmComp->TargetArmLength = CameraArmLength + AddLength;
        }

        //ui ��������� ������ ����� ���� ������ ��ü
        DrawDebugSphere(GetWorld(), LockOnEnemy->GetActorLocation(), 30.f, 12, FColor::Red);
    }
    else
    {
        if (SpringArmComp->GetRelativeLocation() !=FVector::ZeroVector)
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

    if (EnemyCameraCheck()) // true�� ���� ����
    {
        LockOnEnemy = nullptr;
    }
}

void AParentCharacter::LockOff()
{
    FSM = EPlayerState::IDLE;

    bLockOn = false;
    LockOnEnemy = nullptr;
    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
}


void AParentCharacter::StateChanger()
{
    switch (FSM)
    {
    case EPlayerState::IDLE:
    {
        if (MoveDir != FVector2D::ZeroVector)
        {
            FSM = EPlayerState::RUN;
        }
        break;
    }
    case EPlayerState::RUN:
    {
        if (MoveDir == FVector2D::ZeroVector)
        {
            FSM = EPlayerState::IDLE;
        }

        if (GetCharacterMovement()->IsFalling())
        {
            FSM = EPlayerState::JUMP;
        }
        break;
    }
    case EPlayerState::JUMP:
    {
        if (!GetCharacterMovement()->IsFalling())
        {
            FSM = EPlayerState::IDLE;
        }

        break;
    }
    case EPlayerState::FALL:
    {
        if (!GetCharacterMovement()->IsFalling())
        {
            FSM = EPlayerState::IDLE;
        }
        
        break;
    }
    case EPlayerState::ATTACK:
    {

        break;
    }
    case EPlayerState::EVADE:
    {

        break;
    }
    }
    
}

void AParentCharacter::Server_SetKeyDir_Implementation(const FVector2D& Value)
{
	KeyDir = Value;
	KeyDir.Normalize();
}

void AParentCharacter::Multicast_SetKeyDir_Implementation(const FVector2D& Value)
{
    KeyDir = Value;
    KeyDir.Normalize();
}

void AParentCharacter::Server_MoveKey_Implementation()
{
    FVector DirX = GetActorRotation().Vector().RightVector * GetVelocity().X;
    FVector DirY = GetActorRotation().Vector().ForwardVector * GetVelocity().Y;
    MoveDir = FVector2D(DirX) + FVector2D(DirY);
    MoveDir.Normalize();
}
void AParentCharacter::Multicast_MoveKey_Implementation()
{
    FVector DirX = GetActorRotation().Vector().RightVector * GetVelocity().X;
    FVector DirY = GetActorRotation().Vector().ForwardVector * GetVelocity().Y;
    MoveDir = FVector2D(DirX) + FVector2D(DirY);
    MoveDir.Normalize();
}

void AParentCharacter::Server_MoveComplete_Implementation()
{
    MoveDir = FVector2D::ZeroVector;
    KeyDir = FVector2D::ZeroVector;
}
void AParentCharacter::Multicast_MoveComplete_Implementation()
{
    MoveDir = FVector2D::ZeroVector;
    KeyDir = FVector2D::ZeroVector;
}

void AParentCharacter::Server_LeftClick_Implementation()
{
}

void AParentCharacter::Multicast_LeftClick_Implementation()
{
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
    GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
    GetCharacterMovement()->bOrientRotationToMovement = false;
}

void AParentCharacter::Server_ShiftKey_Implementation()
{
    LockOn();
}

void AParentCharacter::Server_ShiftKeyComplete_Implementation()
{
    LockOff();
}

void AParentCharacter::Multicast_ShiftKeyStart_Implementation()
{
    GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
    GetCharacterMovement()->bOrientRotationToMovement = false;
}

void AParentCharacter::Multicast_ShiftKey_Implementation()
{

    bLockOn = true;
    LockOn();
}

void AParentCharacter::Multicast_ShiftKeyComplete_Implementation()
{
    LockOff();
}

void AParentCharacter::Server_SpaceKey_Implementation()
{
    switch (FSM)
    {
    case EPlayerState::IDLE:
    {
        FSM = EPlayerState::JUMP;
        Jump();
        break;
    }
    case EPlayerState::RUN:
    {
        FSM = EPlayerState::JUMP;
        Jump();
        break;
    }
    case EPlayerState::JUMP:
    {

        break;
    }
    case EPlayerState::FALL:
    {

        break;
    }
    case EPlayerState::ATTACK:
    {

        break;
    }
    case EPlayerState::EVADE:
    {

        break;
    }
    }
}

void AParentCharacter::Multicast_SpaceKey_Implementation()
{
    switch (FSM)
    {
    case EPlayerState::IDLE:
    {
        FSM = EPlayerState::JUMP;
        Jump();
        break;
    }
    case EPlayerState::RUN:
    {
        FSM = EPlayerState::JUMP;
        Jump();
        break;
    }
    case EPlayerState::JUMP:
    {

        break;
    }
    case EPlayerState::FALL:
    {

        break;
    }
    case EPlayerState::ATTACK:
    {

        break;
    }
    case EPlayerState::EVADE:
    {

        break;
    }
    }
}

void AParentCharacter::Server_Evade_Implementation()
{
}

void AParentCharacter::Multicast_Evade_Implementation()
{
}
