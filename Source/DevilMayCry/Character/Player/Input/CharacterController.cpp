// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterController.h"
#include "EnhancedInput/Public/EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include <GameFramework/CharacterMovementComponent.h>
#include "../ParentCharacter.h"

ACharacterController::ACharacterController(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
}

void ACharacterController::BeginPlay()
{
	Super::BeginPlay();
}

void ACharacterController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void ACharacterController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACharacterController::SetupInputComponent()
{
	Super::SetupInputComponent();

	GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>()->ClearAllMappings();
	GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>()->AddMappingContext(InputMapping, 0);

	UEnhancedInputComponent* EIComp = Cast<UEnhancedInputComponent>(InputComponent);

	EIComp->BindAction(InputActions->MoveInput, ETriggerEvent::Triggered, this, &ACharacterController::Move);
	EIComp->BindAction(InputActions->JumpInput, ETriggerEvent::Triggered, this, &ACharacterController::Jump);
	EIComp->BindAction(InputActions->AttackInput, ETriggerEvent::Triggered, this, &ACharacterController::Attack);
	EIComp->BindAction(InputActions->LookInput, ETriggerEvent::Triggered, this, &ACharacterController::Look);
}


void ACharacterController::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	const FVector ForwardVector = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

	const FVector RightVector = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	GetCharacter()->AddMovementInput(ForwardVector, MovementVector.Y);
	GetCharacter()->AddMovementInput(RightVector, MovementVector.X);
}

void ACharacterController::Jump(const FInputActionValue& Value)
{
	bool bJump = Value.Get<bool>();

	if (bJump)
	{
		const FRotator Rotation = GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector UpVector = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Z);

		GetCharacter()->Jump();
	}
}

void ACharacterController::Attack(const FInputActionValue& Value)
{
	bool bAttack = Value.Get<bool>();

	if (bAttack)
	{
		//공격을 해라~
	}
}

void ACharacterController::Look(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	GetCharacter()->AddControllerYawInput(MovementVector.X);
	GetCharacter()->AddControllerPitchInput(-MovementVector.Y);
}
