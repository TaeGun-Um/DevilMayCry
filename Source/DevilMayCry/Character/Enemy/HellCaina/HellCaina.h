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

	void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void ToggleCollision(bool Value, uint8 Where)override;
	void ToggleCollision(bool Value, EHellCainaCollision Where);

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
	void WalkAnimation();

	UFUNCTION(BlueprintImplementableEvent)
	void WalkLeftAnimation();

	UFUNCTION(BlueprintImplementableEvent)
	void WalkRightAnimation();

	UFUNCTION(BlueprintImplementableEvent)
	void DeadAnimation();


protected:
	//Weapon
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCapsuleComponent> Scythe = nullptr;

private:
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UFsmComponent> HellCainaFsmComp = nullptr;
};
