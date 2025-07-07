// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ParentCharacter.generated.h"


UENUM(BlueprintType)
enum class EPlayerState :uint8
{
	IDLE		UMETA(DisplayName = "IDLE"),
	RUN			UMETA(DisplayName = "RUN"),
	JUMP		UMETA(DisplayName = "JUMP"),
	FALL		UMETA(DisplayName = "FALL"),
	ATTACK		UMETA(DisplayName = "ATTACK"),
	EVADE		UMETA(DisplayName = "EVADE"),
	LOCKON		UMETA(DisplayName = "LOCKON"),
	JUMPBACK	UMETA(DisplayName = "JUMPBACK"),
	COMBOCHECK	UMETA(DisplayName = "COMBOCHECK"),
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
	virtual void Server_MoveKey(const FVector2D& Value);
	UFUNCTION(NetMulticast, Reliable)
	virtual void Multicast_MoveKey(const FVector2D& Value);

	UFUNCTION(Server, Reliable)
	virtual void Server_MoveComplete();
	UFUNCTION(NetMulticast, Reliable)
	virtual void Multicast_MoveComplete();

	UFUNCTION(Server, Reliable)
	virtual void Server_LeftClickStart();
	UFUNCTION(NetMulticast, Reliable)
	virtual void Multicast_LeftClickStart();

	UFUNCTION(Server, Reliable)
	virtual void Server_LeftClickComplete();
	UFUNCTION(NetMulticast, Reliable)
	virtual void Multicast_LeftClickComplete();


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
	virtual void Server_SpaceKeyStart();
	UFUNCTION(NetMulticast, Reliable)
	virtual void Multicast_SpaceKeyStart();
	UFUNCTION(Server, Reliable)
	virtual void Server_SpaceKeyComplete();
	UFUNCTION(NetMulticast, Reliable)
	virtual void Multicast_SpaceKeyComplete();


	virtual void DefaultEvade();
	virtual void DefaultAttack();
	virtual void DefaultJump(float JumpHeight, FVector2D Dir);
	virtual void DefaultJumpBack(float JumpHeight);

	UFUNCTION(BlueprintImplementableEvent)
	bool EnemyCameraCheck();

	UFUNCTION(BlueprintImplementableEvent)
	void EnemyCheck();


	//PlayerState
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UFsmComponent> FsmComp = nullptr;

protected:
	//Jump
	float MaxJumpHeight = 300.f;
	float JumpDistance = 200.f;

private:
	void CameraInit();
	void TurnToEnemy(float DeltaTime);
	void LockOn();
	void LockOff();
	void SetupFsm();

	UFUNCTION(BlueprintCallable)
	void BlueprintChangeState(EPlayerState Value);

	UFUNCTION(BlueprintCallable)
	EPlayerState BlueprintGetCurState();

	UFUNCTION(Server, Reliable)
	void Server_SetKeyDir(const FVector2D& Value);
	UFUNCTION(NetMulticast, Reliable)
	void Multicast_SetKeyDir(const FVector2D& Value);

private:
	//Move
	float RunSpeed = 600.f;
	float WalkSpeed = 400.f;
	UPROPERTY(BlueprintReadOnly , meta = (AllowPrivateAccess = "true"))
	FVector2D MoveDir = FVector2D::ZeroVector;
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FVector2D KeyDir = FVector2D::ZeroVector;

	//Jump
	bool bJumpKey = false;
	FCollisionObjectQueryParams CheckParam;

	//Evade
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool bPrevEvade = false;
	
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
	bool bLockOnKey = false;


	//Attack
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int CurComboCount = 0;
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool bMoveOk = false;

	bool bAttackKey = false;
};
