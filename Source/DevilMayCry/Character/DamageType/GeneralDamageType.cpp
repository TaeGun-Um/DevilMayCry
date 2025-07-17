// Fill out your copyright notice in the Description page of Project Settings.


#include "GeneralDamageType.h"
#include "../Player/ParentCharacter.h"
#include "../Enemy/EnemyBase.h"

void UGeneralDamageType::TypeProcess(TObjectPtr<class AEnemyBase> Enemy)
{
	Super::TypeProcess(Enemy);

	Enemy->DamagedGeneral();
}

void UGeneralDamageType::TypeProcess(TObjectPtr<class AParentCharacter> Player)
{
	Super::TypeProcess(Player);

	Player->Damagedgeneral();
}