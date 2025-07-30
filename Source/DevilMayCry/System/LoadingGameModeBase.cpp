// Fill out your copyright notice in the Description page of Project Settings.


#include "LoadingGameModeBase.h"
#include "DevilMayCry/UI/HUD/LoadingHUD.h"

ALoadingGameModeBase::ALoadingGameModeBase()
{
    HUDClass = ALoadingHUD::StaticClass();
    DefaultPawnClass = nullptr;
    bUseSeamlessTravel = false;

    //PlayerControllerClass = APlayerController_Lobby::StaticClass();
    //GameStateClass = AGameState_Lobby::StaticClass();
    // PlayerStateClass = ALobbyPlayerState::StaticClass();
}

void ALoadingGameModeBase::PostLogin(APlayerController* NewPlayer)
{
    Super::PostLogin(NewPlayer);
    
}

void ALoadingGameModeBase::Logout(AController* Exiting)
{
    Super::Logout(Exiting);

}

void ALoadingGameModeBase::BeginPlay()
{
    Super::BeginPlay();
    UE_LOG(LogTemp, Warning, TEXT("[GameMode] LobbyScene Server Start, (ALobbyGameModeBase::BeginPlay)"));

}