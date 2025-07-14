// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SnatchActor.generated.h"

UCLASS()
class DEVILMAYCRY_API ASnatchActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASnatchActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	void SetOwnerActor(TObjectPtr<class AParentCharacter> owner)
	{
		OwnerActor = owner;
	}

	void StartFire(TObjectPtr<class AEnemyBase> Enemy);

	UFUNCTION(BlueprintCallable)
	bool IsSnatch() const
	{
		return bPullActor;
	}

protected:
	void Launch(float DeltaTime);


	UFUNCTION()
	void OnSphereOverlap(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

private:
	bool bFire = false;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float MaxLength = 1000.f;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class AParentCharacter> OwnerActor = nullptr;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class AEnemyBase> SnatchEnemy = nullptr;

	FVector FirePos = FVector::ZeroVector; 
	FVector StartPos = FVector::ZeroVector;
	float Ratio =0.f;
	float SnatchSpeed = 4.f;


	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USphereComponent> SphereComp = nullptr;
	float ColRadius = 15.f;

	bool bPullActor = false;
	float PullDistance = 100.f;
};
