// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "DevilMayCry/UI/Interface/FSM.h"
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

private:
    void TitleStep();
    void SelectStep();
    void MenuStep();

    UFUNCTION()
    void TitleDelayEvent();

    TArray<FKey> AllKeys;
    FTimerHandle TitleLogoAnimEndHandle;
    FSM TitleFSM;

    bool bIsTitleLogoHandled = false;
    bool bIsTitleDelayEventHandled = false;
    bool bIsTitleMenuHandled = false;
    bool bIsCharacterSelectHandle = false;
    bool bIsMenuSelectHandle = false;

    /// <summary>
    /// Widget Value
    /// </summary>
private:
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

};
