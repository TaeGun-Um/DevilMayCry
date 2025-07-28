// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../EnemyBase.h"
#include "Empusa.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EEmpusaCollision :uint8
{
	LEFT,
	RIGHT,
	ALL,
};

UENUM(BlueprintType)
enum class EEmpusaFsm :uint8
{
	IDLE,
	WALK,
	RUN,
	ATTACK,
	DAMAGED,
	DEAD,
};

UCLASS()
class DEVILMAYCRY_API AEmpusa : public AEnemyBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AEmpusa();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void ToggleCollision(bool Value, uint8 Where)override;
	void ToggleCollision(bool Value, EEmpusaCollision Where);

public:

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void RandomAttack();

	UFUNCTION()
	void OverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void SetupFsm();


	virtual void DamagedDefault() override;

	UFUNCTION(BlueprintImplementableEvent)
	void DamagedAnimation();

	UFUNCTION(BlueprintImplementableEvent)
	void RunAnimation();

	UFUNCTION(BlueprintImplementableEvent)
	void WalkAnimation();

	UFUNCTION(BlueprintImplementableEvent)
	void DeadAnimation();

protected:
	//Weapon
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCapsuleComponent> LeftHand = nullptr;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCapsuleComponent> RightHand = nullptr;

private:
	//Move
	float RunEndRange = 400.f;


	//PlayerState
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UFsmComponent> EmpusaFsmComp = nullptr;
};
