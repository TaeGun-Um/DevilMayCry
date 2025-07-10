// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BGBlackWidget.generated.h"

/**
 * 
 */
UCLASS()
class DEVILMAYCRY_API UBGBlackWidget : public UUserWidget
{
	GENERATED_BODY()
	
    // BG Screen
protected:
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UCanvasPanel> BlackCanvas;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UImage> BGImage;

};
