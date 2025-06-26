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

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION()
	void StateUpdate();
	UFUNCTION()
	void TargetSearch(AActor* Actor, FAIStimulus AIStimulus);

	UPROPERTY(EditAnywhere)
	TObjectPtr<UAIPerceptionComponent> AIPerceptionComp;
protected:

private:
	UPROPERTY(VisibleAnywhere, Category = "AI")
	EAIState CurState = EAIState::Max;

	UPROPERTY(EditAnywhere, Category = "AI")
	TObjectPtr<UBehaviorTree> EnemyBehaviorTree; 

};
