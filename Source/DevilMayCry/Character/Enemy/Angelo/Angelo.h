// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../EnemyBase.h"
#include "Angelo.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EAngeloCollision :uint8
{
	SWORD,
	ALL,
};

UENUM(BlueprintType)
enum class EAngeloFsm :uint8
{
	IDLE,
	RUN,
	ATTACK,
	DAMAGED,
	PARRY,
	DENGEKI,
	RAKURAI,
	WARP,
	STUN,
	DEAD,
};

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

	virtual void ToggleCollision(bool Value, uint8 Where)override;
	void ToggleCollision(bool Value, EAngeloCollision Where);

public:

protected:
	UFUNCTION()
	void OverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void SetupFsm();
	UFUNCTION(BlueprintCallable)
	void BlueprintChangeState(EAngeloFsm State);

	void FireDengeki(float DeltaTime);
	
	UFUNCTION(BlueprintCallable)
	void InitRakurai();

	void FireRakurai(float DeltaTime);

	virtual void DamagedDefault() override;

	UFUNCTION(BlueprintImplementableEvent)
	void DamagedAnimation();

	UFUNCTION(BlueprintImplementableEvent)
	void DengekiAnimation();

	UFUNCTION(BlueprintImplementableEvent)
	void RakuraiAnimation();

	UFUNCTION(BlueprintImplementableEvent)
	void WalkAnimation();

	UFUNCTION(BlueprintImplementableEvent)
	void ParryAnimation();

	UFUNCTION(BlueprintImplementableEvent)
	void AttackAnimation();

	UFUNCTION(BlueprintImplementableEvent)
	void WarpAnimation();

	UFUNCTION(BlueprintImplementableEvent)
	void StunAnimation();

protected:
	//Weapon
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCapsuleComponent> Sword = nullptr;

private:

	//Dengeki
	const float MaxDengekiDelay = 1.f;
	float CurDengekiDelay = 0.f;
	const float DengekiStart = 2500.f;
	const float DengekiEnd = 1500.f;
	
	//Rakurai
	const float RakuraiRadius = 1000.f;
	TArray<FVector> RakuraiPos;
	int32 RakuraiMaxCount = 30;
	int32 RakuraiIndex = 0;
	const float MaxRakuraiDelay = 1.f / RakuraiMaxCount;
	float CurRakuraiDelay = 0.f;
	TArray<class ADelayDamage*> RakuraiPool;

	//Warp
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FVector WarpPos = FVector::ZeroVector;
	float WarpHPRatio = 0.5f;
	bool bWarpDone = false;
	float StunHPRatio = 0.3f;
	float WarpHP = 0.f;




	
	//Name
	FName Parry = TEXT("Parry");
	FName Weapon = TEXT("Weapon");

	FName L_WeaponHand = TEXT("L_WeaponHand");
};