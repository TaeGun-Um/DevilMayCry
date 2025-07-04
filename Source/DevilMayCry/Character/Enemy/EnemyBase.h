// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyBase.generated.h"


UENUM(BlueprintType)
enum class EEnemyState :uint8
{
	IDLE		UMETA(DisplayName = "IDLE"),
	PATROL		UMETA(DisplayName = "PATROL"),
	RUN			UMETA(DisplayName = "RUN"),
	FALL		UMETA(DisplayName = "FALL"),
	ATTACK		UMETA(DisplayName = "ATTACK"),
	DEAD		UMETA(DisplayName = "DEAD"),
};

UCLASS()
class DEVILMAYCRY_API AEnemyBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemyBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION(BlueprintCallable)
	void SetWalkSpeed(float Value);

protected:
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EEnemyState Fsm = EEnemyState::IDLE;

private:

private:
};
