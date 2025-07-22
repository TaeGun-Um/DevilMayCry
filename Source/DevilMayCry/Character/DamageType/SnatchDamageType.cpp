// Fill out your copyright notice in the Description page of Project Settings.


#include "SnatchDamageType.h"
#include "../Player/ParentCharacter.h"
#include "../Enemy/EnemyBase.h"

void USnatchDamageType::TypeProcess(TObjectPtr<class AEnemyBase> Enemy, TObjectPtr<class AActor> DamageCauser)
{
	Super::TypeProcess(Enemy, DamageCauser);

	Enemy->DamagedSnatch();
}

void USnatchDamageType::TypeProcess(TObjectPtr<class AParentCharacter> Player, TObjectPtr<class AActor> DamageCauser)
{
	Super::TypeProcess(Player, DamageCauser);

}