// Fill out your copyright notice in the Description page of Project Settings.


#include "ParentCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "../Enemy/EnemyBase.h"
#include "Kismet/KismetMathLibrary.h"


#include "DrawDebugHelpers.h"

// Sets default values
AParentCharacter::AParentCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


    GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -90.f));
    GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

    CameraInit();    

    
    Tags.Add(TEXT("Player"));
}

// Called when the game starts or when spawned
void AParentCharacter::BeginPlay()
{
	Super::BeginPlay();
    GetCharacterMovement()->JumpZVelocity = 800.f;
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
                FVector2D(0.f, CameraArmLength*0.5f),       // ���� ��
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
    EnemyCheck();
    bLockOn = true;
    GetCharacterMovement()->bOrientRotationToMovement = false;
}

void AParentCharacter::LockOff()
{
    GetCharacterMovement()->bOrientRotationToMovement = true;
    bLockOn = false;
    LockOnEnemy = nullptr;
}


void AParentCharacter::Server_LeftClick()
{
}

void AParentCharacter::Multicast_LeftClick()
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

void AParentCharacter::ShiftKey()
{
}

void AParentCharacter::SpaceKey()
{
}
