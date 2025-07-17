// Fill out your copyright notice in the Description page of Project Settings.


#include "DMC5DamageType.h"
#include "../Player/ParentCharacter.h"
#include "../Enemy/EnemyBase.h"

void UDMC5DamageType::TypeProcess(TObjectPtr<class AEnemyBase> Enemy)
{
	Enemy->DamagedDefault();
}

void UDMC5DamageType::TypeProcess(TObjectPtr<class AParentCharacter> Player)
{

}
