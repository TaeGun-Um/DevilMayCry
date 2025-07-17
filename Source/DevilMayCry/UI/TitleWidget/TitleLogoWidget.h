// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DevilMayCry/UI/BasicWidget/AnimationWidget.h"
#include "TitleLogoWidget.generated.h"

/**
 * 
 */
UCLASS()
class DEVILMAYCRY_API UTitleLogoWidget : public UAnimationWidget
{
	GENERATED_BODY()
	
public:
    void PlayAnim() { PlayAnimation(FadeAnimation); };
    bool IsAnimationEnd() const { return bIsAnimationEnd; }

    UFUNCTION()
    void SetAnimationEnd() { bIsAnimationEnd = true; }

protected:
    virtual bool Initialize() override;

private:
    void VariableSetting();

    FWidgetAnimationDynamicEvent AnimationEndEvent;
    bool bIsAnimationEnd = false;

    /// <summary>
    /// Widget Value
    /// </summary>
private:
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UCanvasPanel> TitleLogoCanvas;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class USizeBox> TitleLogoSizeBox;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UImage> TitleLogoImage;

    UPROPERTY(Meta = (BindWidgetAnim), Transient)
    TObjectPtr<class UWidgetAnimation> FadeAnimation;

};
