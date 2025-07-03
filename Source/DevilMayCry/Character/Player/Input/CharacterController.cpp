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
	EIComp->BindAction(InputActions->MoveInput, ETriggerEvent::Completed, this, &ACharacterController::MoveComplete)
		;
	EIComp->BindAction(InputActions->JumpInput, ETriggerEvent::Started, this, &ACharacterController::JumpStart);
	EIComp->BindAction(InputActions->JumpInput, ETriggerEvent::Completed, this, &ACharacterController::JumpComplete);

	EIComp->BindAction(InputActions->LookInput, ETriggerEvent::Triggered, this, &ACharacterController::Look);

	EIComp->BindAction(InputActions->LockOnInput, ETriggerEvent::Triggered, this, &ACharacterController::ShiftKey);
	EIComp->BindAction(InputActions->LockOnInput, ETriggerEvent::Started, this, &ACharacterController::ShiftKeyStart);
	EIComp->BindAction(InputActions->LockOnInput, ETriggerEvent::Completed, this, &ACharacterController::ShiftKeyComplete);

	EIComp->BindAction(InputActions->LeftClickInput, ETriggerEvent::Started, this, &ACharacterController::LeftClick);

	EIComp->BindAction(InputActions->RightClickInput, ETriggerEvent::Started, this, &ACharacterController::RightClick);

	EIComp->BindAction(InputActions->WheelClickInput, ETriggerEvent::Started, this, &ACharacterController::WheelClick);

	EIComp->BindAction(InputActions->EKeyInput, ETriggerEvent::Started, this, &ACharacterController::EKey);

	EIComp->BindAction(InputActions->EvadeInput, ETriggerEvent::Started, this, &ACharacterController::EvadeKeyStart);
}


void ACharacterController::MoveKey(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	const FVector ForwardVector = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

	const FVector RightVector = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	GetCharacter()->AddMovementInput(ForwardVector, MovementVector.Y);
	GetCharacter()->AddMovementInput(RightVector, MovementVector.X);


	if (HasAuthority())
	{
		ParentChar->Multicast_MoveKey();
		ParentChar->Multicast_SetKeyDir(MovementVector);
	}
	else
	{
		//ParentChar->Multicast_MoveKey();
		//ParentChar->Multicast_SetKeyDir(MovementVector);
		ParentChar->Server_MoveKey();
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
		//ParentChar->Multicast_MoveComplete();
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
		//ParentChar->Multicast_SpaceKeyStart();
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
		//ParentChar->Multicast_ShiftKeyStart();
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
		//ParentChar->Multicast_ShiftKey();
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
		//ParentChar->Multicast_ShiftKeyComplete();
		ParentChar->Server_ShiftKeyComplete();
	}
}

void ACharacterController::LeftClick(const FInputActionValue& Value)
{
	if (HasAuthority())
	{		
		ParentChar->Multicast_LeftClick();
	}
	else
	{
		//ParentChar->Multicast_LeftClick();
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

void ACharacterController::EvadeKeyStart(const FInputActionValue& Value)
{
	if (HasAuthority())
	{
		ParentChar->Multicast_EvadeKeyStart();
	}
	else
	{
		//ParentChar->Multicast_EvadeKeyStart();
		ParentChar->Server_EvadeKeyStart();
	}
}
