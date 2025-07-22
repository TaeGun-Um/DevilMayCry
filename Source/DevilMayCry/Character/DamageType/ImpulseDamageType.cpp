// Fill out your copyright notice in the Description page of Project Settings.


#include "ImpulseDamageType.h"
#include "../Player/ParentCharacter.h"
#include "../Enemy/EnemyBase.h"

void UImpulseDamageType::TypeProcess(TObjectPtr<class AEnemyBase> Enemy, TObjectPtr<class AActor> DamageCauser)
{
	Super::TypeProcess(Enemy, DamageCauser);
}

void UImpulseDamageType::TypeProcess(TObjectPtr<class AParentCharacter> Player, TObjectPtr<class AActor> DamageCauser)
{
	Super::TypeProcess(Player, DamageCauser);

	FVector TempVector = DamageCauser->GetActorLocation()-Player->GetActorLocation();
	TempVector.Normalize();

	Player->SetActorRotation(TempVector.Rotation());
	Player->DamagedImpulse();
}