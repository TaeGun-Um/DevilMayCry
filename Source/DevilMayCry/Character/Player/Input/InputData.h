// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "InputData.generated.h"

/**
 * 
 */
class UInputAction;

UCLASS()
class DEVILMAYCRY_API UInputData : public UDataAsset
{
	GENERATED_BODY()

public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    UInputAction* MoveInput;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    UInputAction* JumpInput;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    UInputAction* AttackInput;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    UInputAction* LookInput;
};
