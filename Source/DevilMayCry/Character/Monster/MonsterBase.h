// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MonsterBase.generated.h"

UCLASS()
class DEVILMAYCRY_API AMonsterBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMonsterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


public:
	
protected:

private:
	int MaxHP = 1000;
	int CurHP = 1000;
	int MoveSpeed = 300.f;


};
