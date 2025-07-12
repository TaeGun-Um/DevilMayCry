// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "TitleHUD.generated.h"

/**
 * 
 */
UCLASS()
class DEVILMAYCRY_API ATitleHUD : public AHUD
{
	GENERATED_BODY()
	
public:
    ATitleHUD();

protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

    UPROPERTY(EditAnywhere, Category = "UI")
    TSubclassOf<class UUserWidget> BGBlackWidgetClass;

    UPROPERTY(EditAnywhere, Category = "UI")
    TSubclassOf<class UUserWidget> TitleLogoWidgetClass;

    UPROPERTY(EditAnywhere, Category = "UI")
    TSubclassOf<class UUserWidget> TitleWidgetClass;

    UPROPERTY(EditAnywhere, Category = "UI")
    TSubclassOf<class UUserWidget> TestWidgetClass;

private:
     UPROPERTY()
     TObjectPtr<class UBlackBGWidget> BGBlackWidgetInstance;

     UPROPERTY()
     TObjectPtr<class UTitleLogoWidget> TitleLogoWidgetInstance;

     UPROPERTY()
     TObjectPtr<class UTitleWidget> TitleWidgetInstance;

     UPROPERTY()
     TObjectPtr<class UTestWidget> TestWidgetInstance;

     UPROPERTY()
     TObjectPtr<class APlayerController> HUDPlayerController;

     FTimerHandle TitleLogoAnimEndHandle;

     bool bIsTitleLogoHandled = false;
     bool bIsTitleBackHandled = false;
     bool bIsTitleMenuHandled = false;

     TArray<FKey> AllKeys;

     UFUNCTION()
     void OnTitleLogoAnimEndDelay();

};
