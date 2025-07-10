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
    virtual bool Initialize() override;

    // Title Screen
protected:
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UCanvasPanel> TitleCanvas;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UImage> TitleBGImage;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UButton> TitleStartButton;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UButton> TitleExitButton;

private:
    UFUNCTION()
    void OnStartClicked();

    UFUNCTION()
    void OnExitClicked();

};
