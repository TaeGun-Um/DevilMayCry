// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DevilMayCry/UI/Interface/UIAnimationInterface.h"
#include "BGBlackWidget.generated.h"

/**
 * 
 */
UCLASS()
class DEVILMAYCRY_API UBGBlackWidget : public UUserWidget, public IUIAnimationInterface
{
	GENERATED_BODY()
	
public:
    virtual bool Initialize() override;
    virtual void AnimInit() override;
    virtual void PlayAnim() override;

    // BG Screen
protected:
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UCanvasPanel> BlackCanvas;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UImage> BGImage;

    UPROPERTY(Meta = (BindWidgetAnim), Transient)
    TObjectPtr<class UWidgetAnimation> FadeAnimation;

private:
    UFUNCTION()
    void AnimFinishedCall();

    FWidgetAnimationDynamicEvent AnimFinishEvent;
};
