// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TestWidget.generated.h"

UENUM(BlueprintType)
enum class ETestTitleMenuType : uint8
{
    MainMenu    UMETA(DisplayName = "MainMenu"),
    Setting             UMETA(DisplayName = "Setting"),
    Exit             UMETA(DisplayName = "Exit"),
    None           UMETA(DisplayName = "None"),
};

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
    TObjectPtr<class USizeBox> TestSizeBox;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UImage> TestSizeImage;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UButton> TestButton0;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UButton> TestButton1;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UButton> TestButton2;

    UPROPERTY(Meta = (BindWidgetAnim), Transient)
    TObjectPtr<class UWidgetAnimation> SizeUpAnimation;

    UFUNCTION()
    void Button0Hover();

    UFUNCTION()
    void Button0UnHover();

    UFUNCTION()
    void Button1Hover();

    UFUNCTION()
    void Button1UnHover();

    UFUNCTION()
    void Button2Hover();

    UFUNCTION()
    void Button2UnHover();

    ETestTitleMenuType MenuType = ETestTitleMenuType::None;
    // FVector2D AbsolutePosition;  // DPI가 적용된 좌상단 위치
    // FVector2D LocalSize;                // 위젯 크기
};
