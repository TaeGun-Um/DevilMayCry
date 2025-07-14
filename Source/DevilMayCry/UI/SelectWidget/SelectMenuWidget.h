// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SelectMenuWidget.generated.h"

UENUM(BlueprintType)
enum class EMenuType : uint8
{
    MainMenu     UMETA(DisplayName = "MainMenu"),
    Setting         UMETA(DisplayName = "Setting"),
    Exit              UMETA(DisplayName = "Exit"),
    None            UMETA(DisplayName = "None"),
};

UCLASS()
class DEVILMAYCRY_API USelectMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
    void PlayFadeAnimation();

protected:
    virtual bool Initialize() override;

private:
    // BackGround Image
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UCanvasPanel> MenuCanvas;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class USizeBox> MenuSizeBox;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UImage> MenuBGImage;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UButton> MenuStartButton;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UButton> MenuSettingButton;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UButton> MenuExitButton;

    UPROPERTY(Meta = (BindWidgetAnim), Transient) // Fade
    TObjectPtr<class UWidgetAnimation> FadeAnimation;

    EMenuType MenuType = EMenuType::None;
};
