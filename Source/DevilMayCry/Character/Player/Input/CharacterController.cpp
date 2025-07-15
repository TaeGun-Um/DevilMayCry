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

	EIComp->BindAction(InputActions->MoveInput, ETriggerEvent::Triggered, this, &ACharacterController::MoveKey);
	EIComp->BindAction(InputActions->MoveInput, ETriggerEvent::Completed, this, &ACharacterController::MoveComplete);

	EIComp->BindAction(InputActions->JumpInput, ETriggerEvent::Started, this, &ACharacterController::JumpStart);
	EIComp->BindAction(InputActions->JumpInput, ETriggerEvent::Completed, this, &ACharacterController::JumpComplete);

	EIComp->BindAction(InputActions->LookInput, ETriggerEvent::Triggered, this, &ACharacterController::Look);

	EIComp->BindAction(InputActions->LockOnInput, ETriggerEvent::Triggered, this, &ACharacterController::ShiftKey);
	EIComp->BindAction(InputActions->LockOnInput, ETriggerEvent::Started, this, &ACharacterController::ShiftKeyStart);
	EIComp->BindAction(InputActions->LockOnInput, ETriggerEvent::Completed, this, &ACharacterController::ShiftKeyComplete);

	EIComp->BindAction(InputActions->LeftClickInput, ETriggerEvent::Started, this, &ACharacterController::LeftClickStart);
	EIComp->BindAction(InputActions->LeftClickInput, ETriggerEvent::Completed, this, &ACharacterController::LeftClickComplete);

	EIComp->BindAction(InputActions->RightClickInput, ETriggerEvent::Started, this, &ACharacterController::RightClickStart);
	EIComp->BindAction(InputActions->RightClickInput, ETriggerEvent::Completed, this, &ACharacterController::RightClickComplete);

	EIComp->BindAction(InputActions->WheelClickInput, ETriggerEvent::Started, this, &ACharacterController::WheelClickStart);
	EIComp->BindAction(InputActions->WheelClickInput, ETriggerEvent::Completed, this, &ACharacterController::WheelClickComplete);

	EIComp->BindAction(InputActions->EKeyInput, ETriggerEvent::Started, this, &ACharacterController::EKey);

	EIComp->BindAction(InputActions->ZKeyInput, ETriggerEvent::Started, this, &ACharacterController::ZKeyStart);
	EIComp->BindAction(InputActions->ZKeyInput, ETriggerEvent::Completed, this, &ACharacterController::ZKeyComplete);
}


void ACharacterController::MoveKey(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	/*const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	const FVector ForwardVector = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

	const FVector RightVector = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	GetCharacter()->AddMovementInput(ForwardVector, MovementVector.Y);
	GetCharacter()->AddMovementInput(RightVector, MovementVector.X);*/


	if (HasAuthority())
	{
		ParentChar->Multicast_MoveKey(MovementVector);
		ParentChar->Multicast_SetKeyDir(MovementVector);
	}
	else
	{
		ParentChar->Server_MoveKey(MovementVector);
		ParentChar->Server_SetKeyDir(MovementVector);
	}
}

void ACharacterController::MoveComplete(const FInputActionValue& Value)
{
	if (HasAuthority())
	{
		ParentChar->Multicast_MoveComplete();
	}
	else
	{
		ParentChar->Server_MoveComplete();
	}
}

void ACharacterController::JumpStart(const FInputActionValue& Value)
{
	if (HasAuthority())
	{
		ParentChar->Multicast_SpaceKeyStart();
	}
	else
	{
		ParentChar->Server_SpaceKeyStart();
	}
}

void ACharacterController::JumpComplete(const FInputActionValue& Value)
{
	if (HasAuthority())
	{
		ParentChar->Multicast_SpaceKeyComplete();
	}
	else
	{
		//ParentChar->Multicast_SpaceKeyComplete();
		ParentChar->Server_SpaceKeyComplete();
	}
}

void ACharacterController::Look(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	GetCharacter()->AddControllerYawInput(MovementVector.X);
	GetCharacter()->AddControllerPitchInput(-MovementVector.Y);
}

void ACharacterController::ShiftKeyStart(const FInputActionValue& Value)
{
	if (HasAuthority())
	{
		ParentChar->Multicast_ShiftKeyStart();
	}
	else
	{
		ParentChar->Server_ShiftKeyStart();
	}
}

void ACharacterController::ShiftKey(const FInputActionValue& Value)
{
	if (HasAuthority())
	{
		ParentChar->Multicast_ShiftKey();
	}
	else
	{
		ParentChar->Server_ShiftKey();
	}
}

void ACharacterController::ShiftKeyComplete(const FInputActionValue& Value)
{
	if (HasAuthority())
	{
		ParentChar->Multicast_ShiftKeyComplete();
	}
	else
	{
		ParentChar->Server_ShiftKeyComplete();
	}
}

void ACharacterController::LeftClickStart(const FInputActionValue& Value)
{
	if (HasAuthority())
	{
		ParentChar->Multicast_LeftClickStart();
	}
	else
	{
		ParentChar->Server_LeftClickStart();
	}
}

void ACharacterController::LeftClickComplete(const FInputActionValue& Value)
{
	if (HasAuthority())
	{
		ParentChar->Multicast_LeftClickComplete();
	}
	else
	{
		ParentChar->Server_LeftClickComplete();
	}
}

void ACharacterController::RightClickStart(const FInputActionValue& Value)
{
	if (HasAuthority())
	{
		ParentChar->Multicast_RightClickStart();
	}
	else
	{
		ParentChar->Server_RightClickStart();
	}
}

void ACharacterController::RightClickComplete(const FInputActionValue& Value)
{
	if (HasAuthority())
	{
		ParentChar->Multicast_RightClickComplete();
	}
	else
	{
		ParentChar->Server_RightClickComplete();
	}
}

void ACharacterController::WheelClickStart(const FInputActionValue& Value)
{
	if (HasAuthority())
	{
		ParentChar->Multicast_WheelClickStart();
	}
	else
	{
		ParentChar->Server_WheelClickStart();
	}
}

void ACharacterController::WheelClickComplete(const FInputActionValue& Value)
{
	if (HasAuthority())
	{
		ParentChar->Multicast_WheelClickComplete();
	}
	else
	{
		ParentChar->Server_WheelClickComplete();
	}
}

void ACharacterController::EKey(const FInputActionValue& Value)
{
}

void ACharacterController::ZKeyStart(const FInputActionValue& Value)
{
	if (HasAuthority())
	{
		ParentChar->Multicast_ZKeyStart();
	}
	else
	{
		ParentChar->Server_ZKeyStart();
	}
}

void ACharacterController::ZKeyComplete(const FInputActionValue& Value)
{
	if (HasAuthority())
	{
		ParentChar->Multicast_ZKeyComplete();
	}
	else
	{
		ParentChar->Server_ZKeyComplete();
	}
}
