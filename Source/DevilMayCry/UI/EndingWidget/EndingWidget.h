// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EndingWidget.generated.h"

/**
 * 
 */
UCLASS()
class DEVILMAYCRY_API UEndingWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetCapturedTexture(UTexture2D* _Tex);

	// Animation
	// void PlayFadeAnimation() { PlayAnimation(FadeAnimation); }
	// void PlayArrowAnimation() { PlayAnimation(ArrowAnimation); }

protected:
	virtual bool Initialize() override;

private:
	void VariableSetting();

	// UPROPERTY(meta = (BindWidget))
	// TObjectPtr<class UCanvasPanel> LoadingCanvas;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UImage> EndingImage;

};
