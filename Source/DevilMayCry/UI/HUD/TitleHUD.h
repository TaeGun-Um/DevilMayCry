// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "DevilMayCry/UI/Interface/FSM.h"
#include "TitleHUD.generated.h"

UENUM(BlueprintType)
enum class ETitleFSMState : uint8
{
    LOGO,
    TITLE,
    CHARACTERSELECT,
    MENU,
    NONE UMETA(Hidden)
};

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
    void ClassSetting();
    void VariableSetting();
    void CreateFSM();

    UFUNCTION()
    void TitleDelayEvent();

    FTimerHandle TitleLogoAnimEndHandle;
    TArray<FKey> AllKeys;
    ETitleFSMState State;
    TObjectPtr<class UFSM> TitleFSM;

    bool bIsLogoHandled = false;
    bool bIsAnykeyHandled = false;
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
