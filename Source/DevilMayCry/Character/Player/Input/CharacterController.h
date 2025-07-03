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
	void LeftClick(const FInputActionValue& Value);
	void RightClick(const FInputActionValue& Value);
	void WheelClick(const FInputActionValue& Value);
	void EKey(const FInputActionValue& Value);

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
