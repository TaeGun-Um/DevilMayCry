// Fill out your copyright notice in the Description page of Project Settings.


#include "SnatchDamageType.h"
#include "../Player/ParentCharacter.h"
#include "../Enemy/EnemyBase.h"

void USnatchDamageType::TypeProcess(TObjectPtr<class AEnemyBase> Enemy)
{
	Super::TypeProcess(Enemy);

	Enemy->DamagedSnatch();
}

void USnatchDamageType::TypeProcess(TObjectPtr<class AParentCharacter> Player)
{
	Super::TypeProcess(Player);

}