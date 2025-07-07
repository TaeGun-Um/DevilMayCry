// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "TitleSceneHUD.generated.h"

/**
 * 
 */
UCLASS()
class DEVILMAYCRY_API ATitleSceneHUD : public AHUD
{
	GENERATED_BODY()
	
public:
    ATitleSceneHUD();

protected:
    virtual void BeginPlay() override;

    UPROPERTY(EditAnywhere, Category = "UI")
    TSubclassOf<class UUserWidget> TitleWidgetClass;

private:
    UPROPERTY()
    TObjectPtr<class UUserWidget> TitleWidgetInstance;

};
