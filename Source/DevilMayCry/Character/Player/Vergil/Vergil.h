// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../ParentCharacter.h"
#include "Vergil.generated.h"

/**
 * 
 */
UCLASS()
class DEVILMAYCRY_API AVergil : public AParentCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AVergil();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:

private:


};
