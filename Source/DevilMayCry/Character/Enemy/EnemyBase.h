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

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void DamagedAnimation(FVector Dir);

private:
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class AParentCharacter> TargetPlayer = nullptr;


	//HP
	float MaxHP = 100.f;
	float CurHP = MaxHP;
};
