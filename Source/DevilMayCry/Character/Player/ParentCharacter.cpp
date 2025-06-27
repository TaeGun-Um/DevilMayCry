// Fill out your copyright notice in the Description page of Project Settings.


#include "ParentCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "../Enemy/EnemyBase.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AParentCharacter::AParentCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

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
    SpringArmComp->TargetArmLength = 600.f;
    SpringArmComp->bUsePawnControlRotation = true;
    SpringArmComp->bDoCollisionTest = true;
    SpringArmComp->ProbeChannel = ECC_Camera;
    SpringArmComp->ProbeSize = 8.0f;

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
		Direction.Normalize();

        FRotator SmoothRot = FMath::RInterpTo(GetActorForwardVector().Rotation(), Direction.Rotation(), DeltaTime, LockOnRatio);
        SmoothRot.Roll = 0.f;
		SmoothRot.Pitch = 0.f;

		SetActorRotation(SmoothRot);


        // 1) Get Rotations
        FRotator CamRot = CameraComp->GetComponentRotation();
        FRotator DestRot = Direction.Rotation();

        // 2) Δ Rot 계산(Shortest Path)
        FRotator DeltaRot = UKismetMathLibrary::NormalizedDeltaRotator(DestRot, CamRot);
        
        // 3) Yaw 오버슈트 시 컨트롤러 움직이기
		const float Limit = 30.f;

		if (DeltaRot.Yaw > Limit )
        {
			AddControllerYawInput(540.f * DeltaTime );
        }
        else if(-Limit > DeltaRot.Yaw)
        {
            AddControllerYawInput(-540.f * DeltaTime);
        }
    }
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
