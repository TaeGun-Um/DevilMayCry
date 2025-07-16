// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameHUD.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"

AInGameHUD::AInGameHUD()
{

}

void AInGameHUD::BeginPlay()
{
    Super::BeginPlay();

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
