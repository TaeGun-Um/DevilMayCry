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

	UFUNCTION(BlueprintCallable)
	void SetCanParry(bool Value)
	{
		bCanParry = Value;
	}


	virtual void DamagedGeneral();
	virtual void DamagedSnatch();
	virtual void DamagedDefault();

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void RandomAttack();


	void DestroyCheck(float DeltaTime);

	void AirCheck(float DeltaTime);

	void TurnToTarget(float DeltaTime);

	UFUNCTION(BlueprintCallable)
	virtual void ToggleCollision(bool Value,uint8 Where = 0);

	bool LimitAngleOver(float Limit);

	void TurnToActor(float DeltaTime);

	void SetCollisionNum(int32 Num)
	{
		CollisionNum = Num;
	}


	TArray<TObjectPtr<UShapeComponent>> CollisionArray;


	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class AParentCharacter> TargetPlayer = nullptr;

	TObjectPtr<class AAIController> AiController = nullptr;

	TObjectPtr<class UAnimInstance> AnimInst = nullptr;


	//HP
	float MaxHP = 100.f;
	float CurHP = MaxHP;
	bool bDead = false;
	const float MaxDeadTime = 2.f;
	float CurDeadTime = MaxDeadTime;

	//Attack
	float AttackDamage = 10.f;
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float AttackRange = 170.f;
	const float LimitAngle = 5.f;

	//HitGravity
	const float AirGravity = 0.2f;
	const float MaxAirTime = 1.f;
	float CurAirTime = MaxAirTime;

	//Snatch
	bool bCanPull = true;

	//Parry
	bool bCanParry = false;
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FName PrevSection;
	
private:
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 CollisionNum = 0;


};
