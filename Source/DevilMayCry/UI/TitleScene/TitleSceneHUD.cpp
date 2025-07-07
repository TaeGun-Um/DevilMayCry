// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleSceneHUD.h"
#include "Blueprint/UserWidget.h"
// #include "TitleSceneWidget.h"
#include "Kismet/GameplayStatics.h"

ATitleSceneHUD::ATitleSceneHUD()
{
    static ConstructorHelpers::FClassFinder<UUserWidget> WidgetClassFinder(TEXT("/Game/UI/WBP_TitleSceneWidget"));
    if (WidgetClassFinder.Succeeded())
    {
        TitleWidgetClass = WidgetClassFinder.Class;
    }
}

void ATitleSceneHUD::BeginPlay()
{
    Super::BeginPlay();

    TitleWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), TitleWidgetClass);
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
}
