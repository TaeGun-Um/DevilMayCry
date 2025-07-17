// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyController.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EAIState : uint8
{
	Idle, 
	Patrol,
	Run,
	Attack,
	Parring,
	Max
};

UCLASS()
class DEVILMAYCRY_API AEnemyController : public AAIController
{
	GENERATED_BODY()
	
public:
	AEnemyController();

	virtual void Tick(float DeltaTime) override;

public:

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "AI")
	TObjectPtr<UBehaviorTree> EnemyBehaviorTree; 
};
