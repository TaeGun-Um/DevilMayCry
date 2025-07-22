// Fill out your copyright notice in the Description page of Project Settings.


#include "GeneralDamageType.h"
#include "../Player/ParentCharacter.h"
#include "../Enemy/EnemyBase.h"

void UGeneralDamageType::TypeProcess(TObjectPtr<class AEnemyBase> Enemy, TObjectPtr<class AActor> DamageCauser)
{
	Super::TypeProcess(Enemy, DamageCauser);

	Enemy->DamagedGeneral();
}

void UGeneralDamageType::TypeProcess(TObjectPtr<class AParentCharacter> Player, TObjectPtr<class AActor> DamageCauser)
{
	Super::TypeProcess(Player, DamageCauser);

	Player->Damagedgeneral();
}