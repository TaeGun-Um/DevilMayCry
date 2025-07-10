// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleHUD.h"
#include "Blueprint/UserWidget.h"
#include "DevilMayCry/UI/BasicWidget/BGBlackWidget.h"
#include "DevilMayCry/UI/TitleWidget/TitleLogoWidget.h"
#include "DevilMayCry/UI/TitleWidget/TitleWidget.h"
#include "Kismet/GameplayStatics.h"

ATitleHUD::ATitleHUD()
{
    static ConstructorHelpers::FClassFinder<UUserWidget> BGBlackWidgetClassFinder(TEXT("/Game/UI/Basic/WBP_BGBlackWidget"));
    if (BGBlackWidgetClassFinder.Succeeded())
    {
        BGBlackWidgetClass = BGBlackWidgetClassFinder.Class;
    }

    static ConstructorHelpers::FClassFinder<UUserWidget> TitleLogoWidgetClassFinder(TEXT("/Game/UI/Title/WBP_TitleLogoWidget"));
    if (TitleLogoWidgetClassFinder.Succeeded())
    {
        TitleLogoWidgetClass = TitleLogoWidgetClassFinder.Class;
    }

    static ConstructorHelpers::FClassFinder<UUserWidget> TitleWidgetClassFinder(TEXT("/Game/UI/Title/WBP_TitleWidget"));
    if (TitleWidgetClassFinder.Succeeded())
    {
        TitleWidgetClass = TitleWidgetClassFinder.Class;
    }
}

void ATitleHUD::BeginPlay()
{
    Super::BeginPlay();

    TitleWidgetInstance = CreateWidget<UTitleWidget>(GetWorld(), TitleWidgetClass);
    if (TitleWidgetClass)
    {
        TitleWidgetInstance->AddToViewport();

        APlayerController* PC = GetOwningPlayerController();
        if (PC)
        {
            PC->SetShowMouseCursor(true);

            FInputModeUIOnly InputMode;
            InputMode.SetWidgetToFocus(TitleWidgetInstance->TakeWidget());
            PC->SetInputMode(InputMode);
        }
    }

    BGBlackWidgetInstance = CreateWidget<UBGBlackWidget>(GetWorld(), BGBlackWidgetClass);
    if (BGBlackWidgetClass)
    {
        BGBlackWidgetInstance->AddToViewport();
        BGBlackWidgetInstance->AnimInit();
        BGBlackWidgetInstance->PlayAnim();
    }

    TitleLogoWidgetInstance = CreateWidget<UTitleLogoWidget>(GetWorld(), TitleLogoWidgetClass);
    if (TitleLogoWidgetClass)
    {
        TitleLogoWidgetInstance->AddToViewport();
        TitleLogoWidgetInstance->AnimInit();
        TitleLogoWidgetInstance->PlayAnim();
    }
}

void ATitleHUD::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (TitleLogoWidgetInstance->IsAnimFinished())
    {
        // UE_LOG(LogTemp, Warning, TEXT("Logo Animation End"));
        TitleLogoWidgetInstance->SetVisibility(ESlateVisibility::Hidden);
        //TitleLogoWidgetInstance->SetVisibility(ESlateVisibility::Visible);
        //TitleLogoWidgetInstance->RemoveFromParent();
    }

    if (BGBlackWidgetInstance->IsAnimFinished())
    {
        // UE_LOG(LogTemp, Warning, TEXT("Logo Animation End"));
        BGBlackWidgetInstance->SetVisibility(ESlateVisibility::Hidden);
        //TitleLogoWidgetInstance->SetVisibility(ESlateVisibility::Visible);
        //TitleLogoWidgetInstance->RemoveFromParent();
    }
}