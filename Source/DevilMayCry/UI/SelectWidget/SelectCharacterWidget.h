// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SelectCharacterWidget.generated.h"

UENUM(BlueprintType)
enum class ECharacterType : uint8
{
	Nero		UMETA(DisplayName = "Nero"),
	Vergil	UMETA(DisplayName = "Vergil"),
	None		UMETA(DisplayName = "None"),
};

UCLASS()
class DEVILMAYCRY_API USelectCharacterWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// Animation
	void PlayFadeAnimation() { PlayAnimation(FadeAnimation); }

	// Getter, Setter
	ECharacterType GetCharacterType() { return CharacterType; }
	void SetUnHovered() { bIsHovered = false; }
	bool IsButtonHovered() { return bIsHovered; }
	void SetIsEnd() { bIsEnd = true; }
	bool GetIsEnd() { return bIsEnd; }

	///////////////// Nero Button Options
	UFUNCTION()
	void NeroButtonClicked();

	UFUNCTION()
	void NeroButtonHovered();

	UFUNCTION()
	void NeroButtonUnHovered();

	///////////////// Vergil Button Options
	UFUNCTION()
	void VergilButtonClicked();

	UFUNCTION()
	void VergilButtonHovered();

	UFUNCTION()
	void VergilButtonUnHovered();

protected:
	virtual bool Initialize() override;

private:
	void VariableSetting();
	void ResetNeroSelect();
	void ResetVergilSelect();

	ECharacterType CharacterType = ECharacterType::None;
	uint8 bIsHovered : 1;
	uint8 bIsEnd : 1;

	/// <summary>
	/// Widget Value
	/// </summary>
private:
	// BackGround Image
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UCanvasPanel> CharacterCanvas;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class USizeBox> CharacterSizeBox;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UImage> CharacterBGImage;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UImage> NeroBackImage;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UImage> VergilBackImage;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UImage> NeroImage;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UImage> VergilImage;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UImage> NeroTegImage;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UImage> NeroLineImage;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UImage> VergilTegImage;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UImage> VergilLineImage;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> NeroExTextBox;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> NeroTextBox;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> VergilExTextBox;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> VergilTextBox;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> NeroButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> VergilButton;

	UPROPERTY(Meta = (BindWidgetAnim), Transient) // Fade
	TObjectPtr<class UWidgetAnimation> FadeAnimation;

	UPROPERTY(Meta = (BindWidgetAnim), Transient) // NeroSelect
	TObjectPtr<class UWidgetAnimation> NeroSelectAnimation;

	UPROPERTY(Meta = (BindWidgetAnim), Transient) // VergilSelect
	TObjectPtr<class UWidgetAnimation> VergilSelectAnimation;

	//////////////// Material for GrayScale
	UPROPERTY()
	TObjectPtr<class UMaterialInstanceDynamic> NeroBackMaterial;

	UPROPERTY()
	TObjectPtr<class UMaterialInstanceDynamic> VergilBackMaterial;

	UPROPERTY()
	TObjectPtr<class UMaterialInstanceDynamic> NeroMaterial;

	UPROPERTY()
	TObjectPtr<class UMaterialInstanceDynamic> VergilMaterial;

	UPROPERTY()
	TObjectPtr<class UMaterialInstanceDynamic> NeroTagMaterial;

	UPROPERTY()
	TObjectPtr<class UMaterialInstanceDynamic> NeroLineMaterial;

	UPROPERTY()
	TObjectPtr<class UMaterialInstanceDynamic> VergilTagMaterial;

	UPROPERTY()
	TObjectPtr<class UMaterialInstanceDynamic> VergilLineMaterial;
};
