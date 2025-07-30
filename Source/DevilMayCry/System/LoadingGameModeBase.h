// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LoadingGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class DEVILMAYCRY_API ALoadingGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ALoadingGameModeBase();

protected:
	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void Logout(AController* Exiting) override;
	virtual void BeginPlay() override;

private:

};
