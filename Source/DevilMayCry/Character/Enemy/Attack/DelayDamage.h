// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DelayDamage.generated.h"

USTRUCT()
struct FDelayDamageSetting
{
	GENERATED_USTRUCT_BODY()

	FVector Pos = FVector::ZeroVector;
	float MaxDamageDelay = 1.f;
	float Damage = 10.f;
	float Radius = 10.f;
	TArray<TObjectPtr<AActor>> IgnoreList;
	TSubclassOf <class UDamageType> DamageType = UDamageType::StaticClass();
};


UCLASS()
class DEVILMAYCRY_API ADelayDamage : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADelayDamage();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	void ActiveSwitch(bool Value)
	{
		bActive = Value;
	}

	void SetPos(FVector Pos)
	{
		Setter.Pos = Pos;
	}

	void SetDelay(float Delay)
	{
		Setter.MaxDamageDelay = Delay;
	}
	void SetDamage(float  Damage)
	{
		Setter.Damage = Damage;
	}
	void SetRadius(float Radius)
	{
		Setter.Radius = Radius;
	}
	void SetDamageType(TSubclassOf<class UDamageType> Type)
	{
		Setter.DamageType = Type;
	}

	FDelayDamageSetting Setter;
protected:

private:
	bool bActive = false;
	float CurDamageDelay = Setter.MaxDamageDelay;


	UPROPERTY()
	TObjectPtr<class USceneComponent> SceneComp =nullptr;
};
