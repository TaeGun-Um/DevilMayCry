// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyBase.generated.h"


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
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

public:
	UFUNCTION(BlueprintCallable)
	void SetWalkSpeed(float Value);


	UFUNCTION(BlueprintImplementableEvent)
	void RandomAttack();

	void DamagedGeneral();
	void DamagedSnatch();
	void DamagedDefault();

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void DamagedAnimation(FVector Dir);

	void DestroyCheck(float DeltaTime);

	void AirCheck(float DeltaTime);

	UFUNCTION(BlueprintCallable)
	virtual void ToggleCollision(bool Value,uint8 Where = 0);

private:
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class AParentCharacter> TargetPlayer = nullptr;


	//HP
	const float MaxHP = 100.f;
	float CurHP = MaxHP;
	bool bDead = false;
	const float MaxDeadTime = 2.f;
	float CurDeadTime = MaxDeadTime;

	//HitGravity
	const float AirGravity = 0.2f;
	const float MaxAirTime = 1.f;
	float CurAirTime = MaxAirTime;

	//Snatch
	bool bCanPull = true;


	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 CollisionNum = 0;
};
