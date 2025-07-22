// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/DamageType.h"
#include "DMC5DamageType.generated.h"

/**
 *
 */
UCLASS(Abstract)
class DEVILMAYCRY_API UDMC5DamageType : public UDamageType
{
	GENERATED_BODY()

public:
	virtual void TypeProcess(TObjectPtr<class AEnemyBase> Enemy, TObjectPtr<class AActor> DamageCauser);
	virtual void TypeProcess(TObjectPtr<class AParentCharacter> Player, TObjectPtr<class AActor> DamageCauser);
};
