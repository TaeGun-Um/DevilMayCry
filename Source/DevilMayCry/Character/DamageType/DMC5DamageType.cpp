// Fill out your copyright notice in the Description page of Project Settings.


#include "DMC5DamageType.h"
#include "../Player/ParentCharacter.h"
#include "../Enemy/EnemyBase.h"

void UDMC5DamageType::TypeProcess(TObjectPtr<class AEnemyBase> Enemy, TObjectPtr<class AActor> DamageCauser)
{
	Enemy->DamagedDefault();
}

void UDMC5DamageType::TypeProcess(TObjectPtr<class AParentCharacter> Player, TObjectPtr<class AActor> DamageCauser)
{

}
