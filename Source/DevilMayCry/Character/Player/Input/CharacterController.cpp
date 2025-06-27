// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterController.h"
#include "../ParentCharacter.h"
#include "EnhancedInput/Public/EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include <GameFramework/CharacterMovementComponent.h>

ACharacterController::ACharacterController(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
}

void ACharacterController::BeginPlay()
{
	Super::BeginPlay();

	ParentChar = Cast<AParentCharacter>(GetCharacter());
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

	//GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>()->ClearAllMappings();
	GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>()->AddMappingContext(InputMapping, 0);

	KeyBinding();
}

void ACharacterController::KeyBinding()
{
	UEnhancedInputComponent* EIComp = Cast<UEnhancedInputComponent>(InputComponent);

	EIComp->BindAction(InputActions->MoveInput, ETriggerEvent::Triggered, this, &ACharacterController::Move);
	EIComp->BindAction(InputActions->JumpInput, ETriggerEvent::Triggered, this, &ACharacterController::Jump);
	EIComp->BindAction(InputActions->LookInput, ETriggerEvent::Triggered, this, &ACharacterController::Look);
	EIComp->BindAction(InputActions->LockOnInput, ETriggerEvent::Triggered, this, &ACharacterController::LockOn);
	EIComp->BindAction(InputActions->LeftClickInput, ETriggerEvent::Triggered, this, &ACharacterController::LeftClick);
	EIComp->BindAction(InputActions->RightClickInput, ETriggerEvent::Triggered, this, &ACharacterController::RightClick);
	EIComp->BindAction(InputActions->WheelClickInput, ETriggerEvent::Triggered, this, &ACharacterController::WheelClick);
	EIComp->BindAction(InputActions->EKeyInput, ETriggerEvent::Triggered, this, &ACharacterController::EKey);
	EIComp->BindAction(InputActions->TestInput, ETriggerEvent::Triggered, this, &ACharacterController::TestFunc);
}


void ACharacterController::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (ParentChar->IsAttackNow())
	{
		return;
	}


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

	if (ParentChar->IsAttackNow())
	{
		return;
	}

	if (bJump)
	{
		GetCharacter()->Jump();
	}
}

void ACharacterController::Look(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	GetCharacter()->AddControllerYawInput(MovementVector.X);
	GetCharacter()->AddControllerPitchInput(-MovementVector.Y);
}

void ACharacterController::LockOn(const FInputActionValue& Value)
{
	bool bDown = Value.Get<bool>();
	if (bDown)
	{
		ParentChar->EnemyCheck();
		ParentChar->SetLockOnValue(true);
		ParentChar->GetCharacterMovement()->bOrientRotationToMovement = false;

	}
	else
	{

		ParentChar->GetCharacterMovement()->bOrientRotationToMovement = true;
		ParentChar->SetLockOnValue(false);
		ParentChar->SetEnemy(nullptr);
	}
}

void ACharacterController::LeftClick(const FInputActionValue& Value)
{
	bool bClick = Value.Get<bool>();

	if (HasAuthority())
	{		
		ParentChar->Multicast_LeftClick();
	}
	else
	{
		ParentChar->Multicast_LeftClick();
		ParentChar->Server_LeftClick();
	}

}

void ACharacterController::RightClick(const FInputActionValue& Value)
{
}

void ACharacterController::WheelClick(const FInputActionValue& Value)
{
}

void ACharacterController::EKey(const FInputActionValue& Value)
{
}

void ACharacterController::TestFunc(const FInputActionValue& Value)
{
	float Value16 = Value.Get<float>();
	UE_LOG(LogTemp, Warning, TEXT("%f"), Value16);
}
