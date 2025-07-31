// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameHUD.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "DevilMayCry/UI/InGameWidget/InGameWidget.h"

AInGameHUD::AInGameHUD()
{
    ClassSetting();
}

void AInGameHUD::BeginPlay()
{
    Super::BeginPlay();
    VariableSetting();

    APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    if (PC)
    {
        PC->SetShowMouseCursor(false);
        FInputModeGameOnly InputMode;
        PC->SetInputMode(InputMode);
    }
}

void AInGameHUD::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    
    if (!bLoggedOnce)
    {
        ++Count;
        if (Count > 10)
        {
            bLoggedOnce = true;
        }

        UWorld* World = GetWorld();
        if (World)
        {
            APlayerController* PC = UGameplayStatics::GetPlayerController(World, 0);
            if (PC)
            {
                FString PCName = PC->GetClass()->GetName();
                UE_LOG(LogTemp, Warning, TEXT("PlayerController Class: %s"), *PCName);
            }

            AGameModeBase* GameMode = UGameplayStatics::GetGameMode(World);
            if (GameMode)
            {
                FString GMName = GameMode->GetClass()->GetName();
                UE_LOG(LogTemp, Warning, TEXT("GameMode Class: %s"), *GMName);
            }
        }
    }
}

void AInGameHUD::CaptureScreenshot()
{
    FScreenshotRequest::RequestScreenshot(TEXT("EndingScreen.png"), false, false);
}

void AInGameHUD::ClassSetting()
{
    static ConstructorHelpers::FClassFinder<UUserWidget> InGameWidgetClassFinder(TEXT("/Game/UI/InGame/WBP_InGameWidget"));
    if (InGameWidgetClassFinder.Succeeded())
    {
        InGameWidgetClass = InGameWidgetClassFinder.Class;
    }
}

void AInGameHUD::VariableSetting()
{
    InGameWidgetInstance = CreateWidget<UInGameWidget>(GetWorld(), InGameWidgetClass);
    InGameWidgetInstance->AddToViewport();
}


