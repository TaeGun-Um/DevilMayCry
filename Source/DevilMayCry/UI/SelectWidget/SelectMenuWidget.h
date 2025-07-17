// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SelectMenuWidget.generated.h"

UENUM(BlueprintType)
enum class EMenuType : uint8
{
    Start            UMETA(DisplayName = "Start"),
    Setting         UMETA(DisplayName = "Setting"),
    Prev             UMETA(DisplayName = "Prev"),
    None            UMETA(DisplayName = "None"),
};

UCLASS()
class DEVILMAYCRY_API USelectMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
    // Animation
    void PlayFadeAnimation();

    // Getter, Setter
    EMenuType GetMenuType();
    void SetUnHovered();
    bool IsButtonHovered();
    void SetIsEnd();
    bool GetIsEnd();

    ///////////////// Start Button Options
    UFUNCTION()
    void StartButtonClicked();

    UFUNCTION()
    void StartButtonHovered();

    UFUNCTION()
    void StartButtonUnHovered();

    ///////////////// Setting Button Options
    UFUNCTION()
    void SettingButtonClicked();

    UFUNCTION()
    void SettingButtonHovered();

    UFUNCTION()
    void SettingButtonUnHovered();

    ///////////////// Prev Button Options
    UFUNCTION()
    void PrevButtonClicked();

    UFUNCTION()
    void PrevButtonHovered();

    UFUNCTION()
    void PrevButtonUnHovered();

protected:
    virtual bool Initialize() override;

private:
    void VariableSetting();

    EMenuType MenuType = EMenuType::None;
    uint8 bIsHovered : 1;
    uint8 bIsEnd : 1;

/// <summary>
/// Widget Value
/// </summary>
private:
    // BackGround Image
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UCanvasPanel> MenuCanvas;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class USizeBox> MenuSizeBox;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UImage> MenuBGImage;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UImage> MenuSizeImage;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UImage> UserBackImage;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UImage> UserImage00;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UImage> UserImage01;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UImage> UserImage02;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UImage> UserImage03;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UButton> MenuStartButton;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UButton> MenuSettingButton;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UButton> MenuPrevButton;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UTextBlock> MenuStartTextBox;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UTextBlock> MenuSettingTextBox;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UTextBlock> MenuPrevTextBox;
    
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UTextBlock> UserTextBox00;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UTextBlock> UserTextBox01;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UTextBlock> UserTextBox02;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UTextBlock> UserTextBox03;

    UPROPERTY(Meta = (BindWidgetAnim), Transient) // Fade
    TObjectPtr<class UWidgetAnimation> FadeAnimation;

    UPROPERTY(Meta = (BindWidgetAnim), Transient) // Fade
    TObjectPtr<class UWidgetAnimation> SizeUpAnimation;

};
