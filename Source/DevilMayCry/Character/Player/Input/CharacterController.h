// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputData.h"
#include "CharacterController.generated.h"

/**
 * 
 */

struct FInputActionValue;

UCLASS()
class DEVILMAYCRY_API ACharacterController : public APlayerController
{
	GENERATED_BODY()

public:
	ACharacterController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	void MoveKey(const FInputActionValue& Value);
	void MoveComplete(const FInputActionValue& Value);
	void JumpStart(const FInputActionValue& Value);
	void JumpComplete(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void ShiftKeyStart(const FInputActionValue& Value);
	void ShiftKey(const FInputActionValue& Value);
	void ShiftKeyComplete(const FInputActionValue& Value);
	void LeftClickStart(const FInputActionValue& Value);
	void LeftClickComplete(const FInputActionValue& Value);
	void RightClickStart(const FInputActionValue& Value);
	void RightClickComplete(const FInputActionValue& Value);
	void WheelClickStart(const FInputActionValue& Value);
	void WheelClickComplete(const FInputActionValue& Value);
	void EKey(const FInputActionValue& Value);
	void ZKeyStart(const FInputActionValue& Value);
	void ZKeyComplete(const FInputActionValue& Value);
	

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Tick(float DeltaTime) override;

	virtual void SetupInputComponent() override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	class UInputMappingContext* InputMapping;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	class UInputData* InputActions;

private:
	void KeyBinding();

private:
	TObjectPtr<class AParentCharacter> ParentChar = nullptr;
};
