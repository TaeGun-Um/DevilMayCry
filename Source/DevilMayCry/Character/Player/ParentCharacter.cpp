// Fill out your copyright notice in the Description page of Project Settings.


#include "ParentCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AParentCharacter::AParentCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


    GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -90.f));
    GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

    CameraInit();
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

void AParentCharacter::MoveKey(bool Value)
{
    bWantMove = Value;
}

void AParentCharacter::LeftClick()
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
