// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ParentCharacter.generated.h"


UENUM(BlueprintType)
enum class EPlayerState :uint8
{
	IDLE	UMETA(DisplayName = "IDLE"),
	RUN		UMETA(DisplayName = "RUN"),
	JUMP	UMETA(DisplayName = "JUMP"),
	FALL	UMETA(DisplayName = "FALL"),
	ATTACK	UMETA(DisplayName = "ATTACK"),
	EVADE	UMETA(DisplayName = "EVADE"),
};


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

	TObjectPtr<class AEnemyBase> GetLockOnEnemy() const
	{
		return LockOnEnemy;
	}

protected:
	UFUNCTION(Server, Reliable)
	virtual void Server_MoveKey();
	UFUNCTION(NetMulticast, Reliable)
	virtual void Multicast_MoveKey();

	UFUNCTION(Server, Reliable)
	virtual void Server_MoveComplete();
	UFUNCTION(NetMulticast, Reliable)
	virtual void Multicast_MoveComplete();

	UFUNCTION(Server, Reliable)
	virtual void Server_LeftClick();
	UFUNCTION(NetMulticast, Reliable)
	virtual void Multicast_LeftClick();

	virtual void RightClick();

	virtual void WheelClick();

	virtual void EKey();

	UFUNCTION(Server, Reliable)
	virtual void Server_ShiftKeyStart();
	UFUNCTION(Server, Reliable)
	virtual void Server_ShiftKey();
	UFUNCTION(Server, Reliable)
	virtual void Server_ShiftKeyComplete();
	UFUNCTION(NetMulticast, Reliable)
	virtual void Multicast_ShiftKeyStart();
	UFUNCTION(NetMulticast, Reliable)
	virtual void Multicast_ShiftKey();
	UFUNCTION(NetMulticast, Reliable)
	virtual void Multicast_ShiftKeyComplete();

	UFUNCTION(Server, Reliable)
	virtual void Server_SpaceKey();
	UFUNCTION(NetMulticast, Reliable)
	virtual void Multicast_SpaceKey();

	UFUNCTION(Server, Reliable)
	virtual void Server_Evade();
	UFUNCTION(NetMulticast, Reliable)
	virtual void Multicast_Evade();


	UFUNCTION(BlueprintImplementableEvent)
	bool EnemyCameraCheck();

	UFUNCTION(BlueprintImplementableEvent)
	void EnemyCheck();


	//PlayerState
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EPlayerState FSM = EPlayerState::IDLE;


private:
	void CameraInit();
	void TurnToEnemy(float DeltaTime);
	void LockOn();
	void LockOff();
	void StateChanger();
	void SetKeyDir(const FVector2D& Value)
	{
		KeyDir = Value;
		KeyDir.Normalize();
	}

private:

	//Move
	float RunSpeed = 600.f;
	float WalkSpeed = 400.f;
	UPROPERTY(BlueprintReadOnly , meta = (AllowPrivateAccess = "true"))
	FVector2D MoveDir = FVector2D::ZeroVector;
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FVector2D KeyDir = FVector2D::ZeroVector;
	
	//Camera
	float CameraArmLength = 600.f;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UCameraComponent> CameraComp = nullptr;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class USpringArmComponent> SpringArmComp = nullptr;


	//LockOn
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class AEnemyBase> LockOnEnemy = nullptr;
	float LockOnRatio = 5.f;
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float SearchRadius = 2000.f;
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool bLockOn = false;



	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int CurComboCount = 0;
};
