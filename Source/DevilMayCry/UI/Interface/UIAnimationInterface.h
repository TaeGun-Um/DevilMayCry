// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "UIAnimationInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UUIAnimationInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 *
 */
class DEVILMAYCRY_API IUIAnimationInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

protected:
	virtual void AnimInit();
	virtual void PlayAnim();

	uint8 bIsAnimFinished : 1;

private:

};
