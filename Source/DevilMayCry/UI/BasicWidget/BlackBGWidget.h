// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DevilMayCry/UI/BasicWidget/AnimationWidget.h"
#include "BlackBGWidget.generated.h"

/**
 * 
 */
UCLASS()
class DEVILMAYCRY_API UBlackBGWidget : public UAnimationWidget
{
	GENERATED_BODY()
	
public:

protected:
    virtual bool Initialize() override;

private:
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UCanvasPanel> BlackCanvas;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UImage> BGImage;

};
