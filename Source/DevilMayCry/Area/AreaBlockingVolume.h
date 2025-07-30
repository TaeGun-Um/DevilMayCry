// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/BlockingVolume.h"
#include "AreaBlockingVolume.generated.h"

/**
 *
 */
UCLASS()
class DEVILMAYCRY_API AAreaBlockingVolume : public ABlockingVolume
{
	GENERATED_BODY()

public:
	AAreaBlockingVolume();

protected:
	virtual void PostInitializeComponents() override;

#if WITH_EDITOR
	virtual void LoadedFromAnotherClass(const FName& OldClassName) override;
	virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedEvent) override;
#endif

private:
};
