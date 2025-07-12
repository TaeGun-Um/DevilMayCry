// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TestWidget.generated.h"

/**
 * 
 */
UCLASS()
class DEVILMAYCRY_API UTestWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

protected:

private:
    virtual bool Initialize() override;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UCanvasPanel> TestCanvas;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UImage> TestImage;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class USizeBox> TestSizeBox0;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class USizeBox> TestSizeBox1;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UButton> TestButton0;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UButton> TestButton1;

    UFUNCTION()
    void Button0Hover();

    UFUNCTION()
    void Button0UnHover();

    UFUNCTION()
    void Button1Hover();

    UFUNCTION()
    void Button1UnHover();
};
