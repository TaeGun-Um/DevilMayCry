// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DevilMayCry/UI/Interface/UIAnimationInterface.h"
#include "TitleLogoWidget.generated.h"

/**
 * 
 */
UCLASS()
class DEVILMAYCRY_API UTitleLogoWidget : public UUserWidget, public IUIAnimationInterface
{
	GENERATED_BODY()
	
public:
    virtual bool Initialize() override;
    virtual void AnimInit() override;
    virtual void PlayAnim() override;

    // Setup Screen
protected:
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UCanvasPanel> TitleLogoCanvas;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class USizeBox> TitleLogoSizeBox;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UImage> TitleLogoImage;

    UPROPERTY(Meta = (BindWidgetAnim), Transient)
    TObjectPtr<class UWidgetAnimation> FadeAnimation;

private:
    UFUNCTION()
    void AnimFinishedCall();

    FWidgetAnimationDynamicEvent AnimFinishEvent;

};
