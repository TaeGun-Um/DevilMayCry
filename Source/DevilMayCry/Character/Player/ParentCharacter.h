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
	void SetAttackNow(bool Value)
	{
		bAttackNow = Value;
	}

	UFUNCTION(BlueprintCallable)
	bool IsAttackNow() const
	{
		return bAttackNow;
	}

protected:
	virtual void LeftClick();
	virtual void RightClick();
	virtual void WheelClick();
	virtual void EKey();
	virtual void ShiftKey();
	virtual void SpaceKey();

private:

	void CameraInit();

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UCameraComponent> CameraComp = nullptr;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class USpringArmComponent> SpringArmComp = nullptr;
	UPROPERTY()
	bool bAttackNow = false;

	UPROPERTY()
	TObjectPtr<class AEnemyBase> LockOnEnemy = nullptr;
};
