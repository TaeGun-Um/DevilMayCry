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

	//������ �ʿ���� ���ɼ��� ���� CharacterController�� �̸� ����� ����
	// Called to bind functionality to input
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


public:
	UFUNCTION(BlueprintCallable)
	void SetAttackNow(bool Value)
	{
		bAttackNow = Value;
	}

	UFUNCTION(BlueprintCallable)
	bool IsAttackNow() const
	{
		return bAttackNow;
	}

	bool IsLockOn()
	{
		return bLockOn;
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

	UFUNCTION(BlueprintCallable)
	void SetEnemy(AEnemyBase* Enemy)
	{
		LockOnEnemy = Enemy;
	}

	void SetLockOnValue(bool Value)
	{
		bLockOn = Value;
	}
	
private:
	void CameraInit();
	void TurnToEnemy(float DeltaTime);

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UCameraComponent> CameraComp = nullptr;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class USpringArmComponent> SpringArmComp = nullptr;

	UPROPERTY()
	bool bAttackNow = false;


	UPROPERTY(EditAnywhere)
	TObjectPtr<class AEnemyBase> LockOnEnemy = nullptr;
	bool bLockOn = false;
	float LockOnRatio = 5.f;
};
