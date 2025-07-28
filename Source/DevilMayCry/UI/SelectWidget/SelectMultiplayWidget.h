// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SelectMultiplayWidget.generated.h"

UENUM(BlueprintType)
enum class EMenuMultiPlayType : uint8
{
    Start            UMETA(DisplayName = "Start"),
    Ready           UMETA(DisplayName = "Ready"),
    Exit              UMETA(DisplayName = "Exit"),
    Message       UMETA(DisplayName = "Message"),
    YesCheck      UMETA(DisplayName = "YesCheck"),
    NoCheck       UMETA(DisplayName = "NoCheck"),
    EnterCheck   UMETA(DisplayName = "EnterCheck"),
    None
};

UCLASS()
class DEVILMAYCRY_API USelectMultiplayWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
    // Animation
    void PlayFadeAnimation();

    // Getter, Setter
    EMenuMultiPlayType GetMenuType() { return MenuType; }
    void SetUnHovered() { bIsHovered = false; }
    bool IsButtonHovered() { return bIsHovered; }
    void SetIsEnd() { bIsEnd = true; }
    bool GetIsEnd() { return bIsEnd; }
    void SetIsChangeMenu(bool _Is = true) { bIsChangeSelectMenu = _Is; }
    bool GetIsChangeMenu() { return bIsChangeSelectMenu; }
    void SetIsChangeLocation2(bool _Is = true) { bIsChangeLocation2 = _Is; }
    bool GetIsChangeLocation2() { return bIsChangeLocation2; }
    void SetHostIP(FString _Text);

    void UpdatePlayerCount();

    ///////////////// Start Button Options
    UFUNCTION()
    void StartButtonClicked();

    UFUNCTION()
    void StartButtonHovered();

    UFUNCTION()
    void StartButtonUnHovered();

    ///////////////// Ready Button Options
    UFUNCTION()
    void ReadyButtonClicked();

    UFUNCTION()
    void ReadyButtonHovered();

    UFUNCTION()
    void ReadyButtonUnHovered();

    ///////////////// Prev Button Options
    UFUNCTION()
    void ExitButtonClicked();

    UFUNCTION()
    void ExitButtonHovered();

    UFUNCTION()
    void ExitButtonUnHovered();

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

protected:
    virtual bool Initialize() override;
    virtual void NativeConstruct() override;
    virtual void NativeDestruct() override;

private:
    void VariableSetting();
    void MessageBox00Visible();
    void MessageBox00Hidden();
    void MessageBox01Visible();
    void MessageBox01Hidden();

    FTimerHandle PlayerCountUpdateHandle;
    EMenuMultiPlayType MenuType = EMenuMultiPlayType::None;
    uint8 bIsHovered : 1;
    uint8 bIsEnd : 1;
    uint8 bIsMessageHandled : 1;
    uint8 bIsChangeLocation2 : 1;
    uint8 bIsChangeSelectMenu : 1;

    FString HostIP = TEXT("");

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
    TObjectPtr<class UButton> MenuReadyButton;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UButton> MenuExitButton;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UTextBlock> MenuStartTextBox;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UTextBlock> MenuReadyTextBox;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UTextBlock> MenuExitTextBox;

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

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UTextBlock> MenuBarTextBox02;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UTextBlock> MenuBarTextBox03;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UImage> MessageImage;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UImage> MessageCheckImage00;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UImage> MessageCheckImage01;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UImage> MessageCheckImage02;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UTextBlock> MessageTextBox;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UTextBlock> MessageCheckTextBox00;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UTextBlock> MessageCheckTextBox01;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UTextBlock> MessageCheckTextBox02;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UButton> MessageCheckButton00;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UButton> MessageCheckButton01;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UButton> MessageCheckButton02;
    
    UPROPERTY(Meta = (BindWidgetAnim), Transient) // Fade
    TObjectPtr<class UWidgetAnimation> FadeAnimation;

    UPROPERTY(Meta = (BindWidgetAnim), Transient) // Fade
    TObjectPtr<class UWidgetAnimation> SizeUpAnimation;

    UPROPERTY(Meta = (BindWidgetAnim), Transient) // Fade
    TObjectPtr<class UWidgetAnimation> MessageAnimation00;

    UPROPERTY(Meta = (BindWidgetAnim), Transient) // Fade
    TObjectPtr<class UWidgetAnimation> MessageAnimation01;

};
