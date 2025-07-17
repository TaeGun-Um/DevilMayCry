// Fill out your copyright notice in the Description page of Project Settings.


#include "ImpulseDamageType.h"
#include "../Player/ParentCharacter.h"
#include "../Enemy/EnemyBase.h"

void UImpulseDamageType::TypeProcess(TObjectPtr<class AEnemyBase> Enemy)
{
	Super::TypeProcess(Enemy);
}

void UImpulseDamageType::TypeProcess(TObjectPtr<class AParentCharacter> Player)
{
	Super::TypeProcess(Player);

	Player->DamagedImpulse();
}