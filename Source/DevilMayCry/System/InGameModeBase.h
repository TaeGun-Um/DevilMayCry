// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "InGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class DEVILMAYCRY_API AInGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AInGameModeBase();
	void EndingStart();

protected:
	UPROPERTY(EditAnywhere, Category = "Ending")
	TSubclassOf<class AEndingSequenceManager> EndingManagerClass;

};
