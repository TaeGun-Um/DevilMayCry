// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TitleWidget.generated.h"

/**
 * 
 */
UCLASS()
class DEVILMAYCRY_API UTitleWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
    void PlayAnim();
    void StopBlinkAnimation();

    // Title Screen
protected:
    virtual bool Initialize() override;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UCanvasPanel> TitleCanvas;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class USizeBox> TitleSizeBox0;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class USizeBox> TitleSizeBox1;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class USizeBox> TitleSizeBox2;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class USizeBox> TitleSizeBox3;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UImage> TitleBGImage;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UImage> TitleAnyKeyImage;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UButton> TitleStartButton;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UButton> TitleExitButton;

    UPROPERTY(Meta = (BindWidgetAnim), Transient)
    TObjectPtr<class UWidgetAnimation> BlinkAnimation;

private:
    UFUNCTION()
    void OnStartClicked();

    UFUNCTION()
    void OnExitClicked();
};
