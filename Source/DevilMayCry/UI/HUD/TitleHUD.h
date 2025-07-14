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
	
    /////////////////// Common
public:
    ATitleHUD();

    /////////////////// TitleStep
public:

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
    TSubclassOf<class UUserWidget> CharacterWidgetClass;

    UPROPERTY(EditAnywhere, Category = "UI")
    TSubclassOf<class UUserWidget> MenuWidgetClass;

private:
     UPROPERTY()
     TObjectPtr<class UBlackBGWidget> BGBlackWidgetInstance;

     UPROPERTY()
     TObjectPtr<class UTitleLogoWidget> TitleLogoWidgetInstance;

     UPROPERTY()
     TObjectPtr<class UTitleWidget> TitleWidgetInstance;

     UPROPERTY()
     TObjectPtr<class USelectCharacterWidget> CharacterWidgetInstance;

     UPROPERTY()
     TObjectPtr<class USelectMenuWidget> MenuWidgetInstance;

     UPROPERTY()
     TObjectPtr<class APlayerController> HUDPlayerController;

     TArray<FKey> AllKeys;
     FTimerHandle TitleLogoAnimEndHandle;

     bool bIsTitleLogoHandled = false;
     bool bIsTitleBackHandled = false;
     bool bIsTitleMenuHandled = false;
     bool bIsCharacterSelectHandle = false;
     bool bIsMenuSelectHandle = false;

     UFUNCTION()
     void OnTitleLogoAnimEndDelay();

     void TitleStep();

     /////////////////// SelectStep
public:

protected:

private:
     void SelectStep();

     /////////////////// MenuStep
public:

protected:

private:
    void MenuStep();

};
