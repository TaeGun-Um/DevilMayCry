// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleHUD.h"
#include "Blueprint/UserWidget.h"
//#include "TitleWidget.h"
#include "Kismet/GameplayStatics.h"

ATitleHUD::ATitleHUD()
{
    //static ConstructorHelpers::FClassFinder<UUserWidget> WidgetClassFinder(TEXT("/Game/UI/WBP_TitleSceneWidget"));
    //if (WidgetClassFinder.Succeeded())
    //{
    //    TitleWidgetClass = WidgetClassFinder.Class;
    //}
}

void ATitleHUD::BeginPlay()
{
    Super::BeginPlay();

    //TitleWidgetInstance = CreateWidget<UTitleWidget>(GetWorld(), TitleWidgetClass);
    //if (TitleWidgetClass)
    //{
    //    TitleWidgetInstance->AddToViewport();
    //    // TitleWidgetInstance->PlayIntroAnimation();

    //    APlayerController* PC = GetOwningPlayerController();
    //    if (PC)
    //    {
    //        PC->SetShowMouseCursor(true);

    //        FInputModeUIOnly InputMode;
    //        InputMode.SetWidgetToFocus(TitleWidgetInstance->TakeWidget());
    //        PC->SetInputMode(InputMode);
    //    }
    //}
}
