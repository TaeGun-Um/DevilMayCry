// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TitleLogoWidget.generated.h"

/**
 * 
 */
UCLASS()
class DEVILMAYCRY_API UTitleLogoWidget : public UUserWidget
{
	GENERATED_BODY()
	
    // Setup Screen
protected:
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UCanvasPanel> TitleLogoCanvas;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UImage> TitleLogoImage;

};
