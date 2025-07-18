// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TitleWidget.generated.h"

UENUM(BlueprintType)
enum class ETitleMenuType : uint8
{
    MainMenu    UMETA(DisplayName = "MainMenu"),
    Setting             UMETA(DisplayName = "Setting"),
    Exit             UMETA(DisplayName = "Exit"),
    None           UMETA(DisplayName = "None"),
};

UCLASS()
class DEVILMAYCRY_API UTitleWidget : public UUserWidget
{
	GENERATED_BODY()

public:
    // Getter, Setter
    void SetVisibileButton();
    ETitleMenuType GetMenuType() { return MenuType; }
    void SetUnHovered() { bIsHovered = false; }
    bool IsButtonHovered() { return bIsHovered; }
    void SetIsEnd(bool _IsEnd) { bIsEnd = _IsEnd; }
    bool GetIsEnd() { return bIsEnd; }

    // Animation
    void PlayFadeAnimation() { PlayAnimation(FadeAnimation); }
    void PlayBlinkAnimation() { PlayAnimation(BlinkAnimation, 0.f, 0); }
    void StopBlinkAnimation();

    ///////////////// Start Button Options
    UFUNCTION()
    void StartButtonClicked();

    UFUNCTION()
    void StartButtonHovered();

    UFUNCTION()
    void StartButtonUnHovered();

    ///////////////// Exit Button Options
    UFUNCTION()
    void ExitButtonClicked();

    UFUNCTION()
    void ExitButtonHovered();

    UFUNCTION()
    void ExitButtonUnHovered();

    // Title Screen
protected:
    virtual bool Initialize() override;

private:
    void VariableSetting();

    ETitleMenuType MenuType = ETitleMenuType::None;
    uint8 bIsHovered : 1;
    uint8 bIsEnd : 1;

    /// <summary>
    /// Widget Value
    /// </summary>
private:
    // BackGround Image
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UCanvasPanel> TitleCanvas;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class USizeBox> TitleSizeBox0;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UImage> TitleBGImage;

    // First Step
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UImage> TitleAnyKeyImage;

    // Second Step
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UImage> TitleSizeImage;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UButton> TitleStartButton;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UButton> TitleExitButton;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UTextBlock> TitleTextBox;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UTextBlock> MainMenuTextBox;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UTextBlock> ExitTextBox;

    // Animations
    UPROPERTY(Meta = (BindWidgetAnim), Transient) // Anykey Animation
    TObjectPtr<class UWidgetAnimation> FadeAnimation;

    UPROPERTY(Meta = (BindWidgetAnim), Transient) // Anykey Animation
    TObjectPtr<class UWidgetAnimation> BlinkAnimation;

    UPROPERTY(Meta = (BindWidgetAnim), Transient) // Title Menu Select Animation
    TObjectPtr<class UWidgetAnimation> SizeUpAnimation;

    UPROPERTY(Meta = (BindWidgetAnim), Transient) // Title Menu Select Animation
    TObjectPtr<class UWidgetAnimation> SizeDownAnimation;

};
 