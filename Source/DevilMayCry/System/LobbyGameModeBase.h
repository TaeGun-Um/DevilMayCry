// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LobbyGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class DEVILMAYCRY_API ALobbyGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ALobbyGameModeBase();

protected:
	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void Logout(AController* Exiting) override;
	virtual void BeginPlay() override;

private:
	FString GetHostIPAddress();
	int32 ConnectedPlayers = 0;

};
