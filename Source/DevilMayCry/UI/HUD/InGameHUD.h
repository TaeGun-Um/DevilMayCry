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

    // UFUNCTION(Client, Reliable)
    // void ClientSetBossHPVisible();

protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

private:
    void VariableSetting();
    void ClassSetting();
    void CaptureScreenshot(); // 이미지 저장(Png)

    int Count = 0;
    bool bLoggedOnce = false;

    UPROPERTY(EditAnywhere, Category = "UI")
    TSubclassOf<class UUserWidget> BGBlackWidgetClass;

    UPROPERTY(EditAnywhere, Category = "UI")
    TSubclassOf<class UUserWidget> InGameWidgetClass;

    UPROPERTY()
    TObjectPtr<class UBlackBGWidget> BGBlackWidgetInstance;

    UPROPERTY()
    TObjectPtr<class UInGameWidget> InGameWidgetInstance;
};
