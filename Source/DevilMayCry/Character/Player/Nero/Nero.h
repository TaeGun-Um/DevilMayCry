// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../ParentCharacter.h"
#include "Nero.generated.h"

/**
 * 
 */

UCLASS()
class DEVILMAYCRY_API ANero : public AParentCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ANero();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void Server_LeftClick_Implementation() override;

	virtual void Multicast_LeftClick_Implementation() override;

	UFUNCTION(BlueprintImplementableEvent)
	void RedQueenCombo();

	UFUNCTION(BlueprintImplementableEvent)
	void JumpAttackCombo();

	virtual void Server_EvadeKeyStart_Implementation()override;
	virtual void Multicast_EvadeKeyStart_Implementation()override;

	UFUNCTION(BlueprintImplementableEvent)
	void Evade();


private:


};
