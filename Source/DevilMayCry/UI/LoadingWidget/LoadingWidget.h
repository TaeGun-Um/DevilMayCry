// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LoadingWidget.generated.h"

/**
 * 
 */
UCLASS()
class DEVILMAYCRY_API ULoadingWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// Animation
	void PlayFadeAnimation() { PlayAnimation(FadeAnimation); }
	void PlayArrowAnimation() { PlayAnimation(ArrowAnimation); }

	UFUNCTION()
	void ArrowClicked();

	UFUNCTION()
	void ArrowHovered();

	UFUNCTION()
	void ArrowUnHovered();

protected:
	virtual bool Initialize() override;

private:
	void VariableSetting();

	int64 Index = 0;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UCanvasPanel> LoadingCanvas;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class USizeBox> LoadingSizeBox;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UImage> LoadingBGImage;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UImage> LoadingProgressBGImage;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UImage> LoadingProgressImage;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UImage> LoadingArrowImage;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> LoadingTextBox;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> LoadingArrowButton;

	UPROPERTY(Meta = (BindWidgetAnim), Transient)
	TObjectPtr<class UWidgetAnimation> ArrowAnimation;

	UPROPERTY(Meta = (BindWidgetAnim), Transient)
	TObjectPtr<class UWidgetAnimation> FadeAnimation;

	UPROPERTY(meta = (BindWidget))
	TArray<FString> StringSlot;
};
