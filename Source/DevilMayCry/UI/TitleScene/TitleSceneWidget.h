// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TitleSceneWidget.generated.h"

/**
 * 
 */
UCLASS()
class DEVILMAYCRY_API UTitleSceneWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
    virtual bool Initialize() override;

    // Root
protected:
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UCanvasPanel> RootCanvas;

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

    // Setup Screen
protected:
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UCanvasPanel> SetupCanvas;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UImage> SetupLogoImage;

private:
    UFUNCTION()
    void OnStartClicked();

    UFUNCTION()
    void OnExitClicked();

};
