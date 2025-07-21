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


	virtual void DamagedDefault() override;


protected:
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UFsmComponent> FsmComp = nullptr;
	//Weapon
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCapsuleComponent> Sword = nullptr;
private:

};
