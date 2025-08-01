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
	END,
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

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void ToggleCollision(bool Value, uint8 Where)override;
	void ToggleCollision(bool Value, EEmpusaCollision Where);

public:

protected:

	UFUNCTION()
	void OverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void SetupFsm();



	virtual void DamagedDefault() override;
	virtual void DamagedGeneral();
	virtual void DamagedSnatch();

	UFUNCTION(BlueprintImplementableEvent)
	void RandomAttack(int32 Index);
	UFUNCTION(NetMulticast, Reliable)
	void Multicast_RandomAttack(int32 Index);

	UFUNCTION(BlueprintImplementableEvent)
	void DamagedAnimation();
	UFUNCTION(NetMulticast, Reliable)
	void Multicast_DamagedAnimation();

	UFUNCTION(BlueprintImplementableEvent)
	void RunAnimation();
	UFUNCTION(NetMulticast,Reliable)
	void Multicast_RunAnimation();

	UFUNCTION(BlueprintImplementableEvent)
	void WalkAnimation();
	UFUNCTION(NetMulticast, Reliable)
	void Multicast_WalkAnimation();

	UFUNCTION(BlueprintImplementableEvent)
	void DeadAnimation();
	UFUNCTION(NetMulticast, Reliable)
	void Multicast_DeadAnimation();

	UFUNCTION(BlueprintImplementableEvent)
	void SnatchAnimation();
	UFUNCTION(NetMulticast, Reliable)
	void Multicast_SnatchAnimation();

protected:
	//Weapon
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCapsuleComponent> LeftHand = nullptr;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCapsuleComponent> RightHand = nullptr;

private:
	//Move
	float RunEndRange = 400.f;

	//Attack
	int32 RandomIndex = -1;
	const int32 RandomMin = 0;
	const int32 RandomMax = 4;

	//PlayerState
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UFsmComponent> EmpusaFsmComp = nullptr;
};
