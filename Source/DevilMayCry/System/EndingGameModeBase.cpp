// Fill out your copyright notice in the Description page of Project Settings.


#include "EndingGameModeBase.h"
#include "DevilMayCry/UI/HUD/EndingHUD.h"

AEndingGameModeBase::AEndingGameModeBase()
{
	HUDClass = AEndingHUD::StaticClass();
	DefaultPawnClass = nullptr;
	bUseSeamlessTravel = false;

	//PlayerControllerClass = APlayerController_Lobby::StaticClass();
	//GameStateClass = AGameState_Lobby::StaticClass();
	//PlayerStateClass = ALobbyPlayerState::StaticClass();
}

void AEndingGameModeBase::BeginPlay()
{
	Super::BeginPlay();

}
