// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../EnemyBase.h"
#include "Angelo.generated.h"

/**
 * 
 */
UCLASS()
class DEVILMAYCRY_API AAngelo : public AEnemyBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAngelo();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


public:

protected:

private:
};
