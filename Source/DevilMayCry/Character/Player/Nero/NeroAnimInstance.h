// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "NeroAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class DEVILMAYCRY_API UNeroAnimInstance : public UAnimInstance
{
	GENERATED_BODY()


public:
	UNeroAnimInstance();

	virtual void NativeUpdateAnimation(float DeltaTime) override;

private:
};
