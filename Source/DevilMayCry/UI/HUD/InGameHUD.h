// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "InGameHUD.generated.h"

/**
 * 
 */
UCLASS()
class DEVILMAYCRY_API AInGameHUD : public AHUD
{
	GENERATED_BODY()
	
    /////////////////// Common
public:
    AInGameHUD();

    /////////////////// TitleStep
public:

protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

    int Count = 0;
    bool bLoggedOnce = false;
};
