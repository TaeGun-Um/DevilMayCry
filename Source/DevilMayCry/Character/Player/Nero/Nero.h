// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../ParentCharacter.h"
#include "Nero.generated.h"

/**
 *
 */

UCLASS()
class DEVILMAYCRY_API ANero : public AParentCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ANero();

protected:
	// Called when the game starts or when spawnedS
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


protected:
	virtual void Attack() override;
	virtual void LockOnEvade() override;
	virtual void Jumping(float JumpHeight, FVector2D Dir, bool bBack = false) override;
	virtual void ZKeyStart()override;
	virtual void ZKeyEnd()override;
	virtual void Shift_WheelClick()override;
	virtual void WheelClick()override;
	virtual void RightClick()override;



	virtual void DamagedImpulse()override;
	virtual void Damagedgeneral()override;



	virtual void ToggleCollision(bool Value)override;

	UFUNCTION(BlueprintImplementableEvent)
	void RedQueenCombo();

	UFUNCTION(BlueprintImplementableEvent)
	void JumpAttackCombo();

	UFUNCTION(BlueprintImplementableEvent)
	void Evade();

	UFUNCTION(BlueprintImplementableEvent)
	void DamagedImpulseAnim();

	UFUNCTION(BlueprintImplementableEvent)
	void DamagedgeneralAnim();

	UFUNCTION()
	void OverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);




	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class ASnatchActor> Snatcher = nullptr;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UArmComponent> ArmComp = nullptr;

	//Weapon
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCapsuleComponent> SwordCollision = nullptr;

private:
	float SwordDamage = 10.f;
	float GunDamage = 10.f;

};
