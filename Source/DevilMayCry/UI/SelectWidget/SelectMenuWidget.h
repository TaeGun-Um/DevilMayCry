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
    Create          UMETA(DisplayName = "Create"),
    Join              UMETA(DisplayName = "Join"),
    Message       UMETA(DisplayName = "Message"),
    YesCheck      UMETA(DisplayName = "YesCheck"),
    NoCheck       UMETA(DisplayName = "NoCheck"),
    EnterCheck   UMETA(DisplayName = "EnterCheck"),
    BackCheck    UMETA(DisplayName = "BackCheck"),
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

    ///////////////// Server Button Options
    UFUNCTION()
    void CreateButtonClicked();

    UFUNCTION()
    void CreateButtonHovered();

    UFUNCTION()
    void CreateButtonUnHovered();

    UFUNCTION()
    void JoinButtonClicked();

    UFUNCTION()
    void JoinButtonHovered();

    UFUNCTION()
    void JoinButtonUnHovered();
    
    UFUNCTION()
    void ResetClicked();

    UFUNCTION()
    void YesButtonClicked();

    UFUNCTION()
    void YesButtonHovered();

    UFUNCTION()
    void YesButtonUnHovered();

    UFUNCTION()
    void NoButtonClicked();

    UFUNCTION()
    void NoButtonHovered();

    UFUNCTION()
    void NoButtonUnHovered();

    UFUNCTION()
    void EnterButtonClicked();

    UFUNCTION()
    void EnterButtonHovered();

    UFUNCTION()
    void EnterButtonUnHovered();

    UFUNCTION()
    void BackButtonClicked();

    UFUNCTION()
    void BackButtonHovered();

    UFUNCTION()
    void BackButtonUnHovered();

protected:
    virtual bool Initialize() override;

private:
    void VariableSetting();
    void MessageBox00Visible();
    void MessageBox00Hidden();
    void MessageBox01Visible();
    void MessageBox01Hidden();
    void MessageBox02Visible();
    void MessageBox02Hidden();

    EMenuType MenuType = EMenuType::None;
    uint8 bIsHovered : 1;
    uint8 bIsEnd : 1;
    uint8 bIsMultiplayHandled : 1;

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
    TObjectPtr<class UImage> MenuMissionImage;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UImage> MenuBarImage00;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UImage> MenuBarImage01;

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

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UTextBlock> MenuBarTextBox00;
    
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UTextBlock> MenuBarTextBox01;

    UPROPERTY(Meta = (BindWidgetAnim), Transient) // Fade
    TObjectPtr<class UWidgetAnimation> FadeAnimation;

    UPROPERTY(Meta = (BindWidgetAnim), Transient) // Fade
    TObjectPtr<class UWidgetAnimation> SizeUpAnimation;

    ///// Server UI
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UButton> ResetStateButton;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UButton> CreateRoomButton;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UButton> JoinRoomButton;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UImage> MultiPlayImage;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UImage> MessageImage;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UImage> MessageCheckImage00;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UImage> MessageCheckImage01;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UImage> MessageCheckImage02;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UImage> MessageCheckImage03;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UImage> IPAddressImage;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UTextBlock> MessageTextBox;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UTextBlock> MessageCheckTextBox00;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UTextBlock> MessageCheckTextBox01;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UTextBlock> MessageCheckTextBox02;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UTextBlock> MessageCheckTextBox03;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UButton> MessageCheckButton00;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UButton> MessageCheckButton01;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UButton> MessageCheckButton02;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UButton> MessageCheckButton03;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UTextBlock> MultiPlayTextBox00;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UTextBlock> MultiPlayTextBox01;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UEditableText> IPAddressTextBox;

    UPROPERTY(Meta = (BindWidgetAnim), Transient) // Fade
    TObjectPtr<class UWidgetAnimation> MultiplayAnimation;

    UPROPERTY(Meta = (BindWidgetAnim), Transient) // Fade
    TObjectPtr<class UWidgetAnimation> MessageAnimation00;

    UPROPERTY(Meta = (BindWidgetAnim), Transient) // Fade
    TObjectPtr<class UWidgetAnimation> MessageAnimation01;

};
