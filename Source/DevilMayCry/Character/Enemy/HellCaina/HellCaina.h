// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../EnemyBase.h"
#include "HellCaina.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EHellCainaCollision :uint8
{
	SCYTHE,
	ALL,
};

UENUM(BlueprintType)
enum class EHellCainaFsm :uint8
{
	IDLE,
	WALK,
	ATTACK,
	DAMAGED,
	DEAD,
	END,
};

UCLASS()
class DEVILMAYCRY_API AHellCaina : public AEnemyBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AHellCaina();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void ToggleCollision(bool Value, uint8 Where)override;
	void ToggleCollision(bool Value, EHellCainaCollision Where);

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
	void WalkAnimation();
	UFUNCTION(NetMulticast, Reliable)
	void Multicast_WalkAnimation();

	UFUNCTION(BlueprintImplementableEvent)
	void WalkLeftAnimation();
	UFUNCTION(NetMulticast, Reliable)
	void Multicast_WalkLeftAnimation();

	UFUNCTION(BlueprintImplementableEvent)
	void WalkRightAnimation();
	UFUNCTION(NetMulticast, Reliable)
	void Multicast_WalkRightAnimation();

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
	TObjectPtr<class UCapsuleComponent> Scythe = nullptr;

private:
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UFsmComponent> HellCainaFsmComp = nullptr;


	//Attack
	int32 RandomIndex = -1;
	const int32 RandomMin = 0;
	const int32 RandomMax = 1;
};
