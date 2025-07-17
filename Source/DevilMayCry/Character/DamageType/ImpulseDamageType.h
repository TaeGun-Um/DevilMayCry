// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DMC5DamageType.h"
#include "ImpulseDamageType.generated.h"

/**
 * 
 */
UCLASS()
class DEVILMAYCRY_API UImpulseDamageType : public UDMC5DamageType
{
	GENERATED_BODY()

public:
	virtual void TypeProcess(TObjectPtr<class AEnemyBase> Enemy);
	virtual void TypeProcess(TObjectPtr<class AParentCharacter> Player);
};
