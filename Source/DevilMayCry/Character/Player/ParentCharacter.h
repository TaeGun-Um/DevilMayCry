// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ParentCharacter.generated.h"

UCLASS(Abstract)
class AParentCharacter : public ACharacter
{
	GENERATED_BODY()

	friend class ACharacterController;

public:
	// Sets default values for this character's properties
	AParentCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//당장은 필요없을 가능성이 높음 CharacterController가 이를 대신할 예정
	// Called to bind functionality to input
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


public:

	UFUNCTION(BlueprintCallable)
	bool IsAttackNow() const
	{
		return bAttackNow;
	}

	bool IsLockOn()
	{
		return bLockOn;
	}

	TObjectPtr<class AEnemyBase> GetLockOnEnemy() const
	{
		return LockOnEnemy;
	}

protected:
	virtual void Server_LeftClick();
	virtual void Multicast_LeftClick();
	virtual void RightClick();
	virtual void WheelClick();
	virtual void EKey();
	virtual void ShiftKey();
	virtual void SpaceKey();

	UFUNCTION(BlueprintImplementableEvent)
	void EnemyCheck();
	
	
private:
	void CameraInit();
	void TurnToEnemy(float DeltaTime);
	void LockOn();
	void LockOff();

private:
	//Camera
	float CameraArmLength = 600.f;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UCameraComponent> CameraComp = nullptr;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class USpringArmComponent> SpringArmComp = nullptr;


	//LockOn
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class AEnemyBase> LockOnEnemy = nullptr;
	bool bLockOn = false;
	float LockOnRatio = 5.f;
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float SearchRadius = 1500.f;


	//Attack
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool bAttackNow = false;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int CurComboCount = 0;
};
