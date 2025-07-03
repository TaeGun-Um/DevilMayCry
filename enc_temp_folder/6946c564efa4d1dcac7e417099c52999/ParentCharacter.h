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
	LOCKON	UMETA(DisplayName = "LOCKON"),
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

	UFUNCTION(Server, UnReliable)
	virtual void Server_MoveComplete();
	UFUNCTION(NetMulticast, UnReliable)
	virtual void Multicast_MoveComplete();

	UFUNCTION(Server, Reliable)
	virtual void Server_LeftClick();
	UFUNCTION(NetMulticast, Reliable)
	virtual void Multicast_LeftClick();

	virtual void RightClick();

	virtual void WheelClick();

	virtual void EKey();

	UFUNCTION(Server, UnReliable)
	virtual void Server_ShiftKeyStart();
	UFUNCTION(Server, UnReliable)
	virtual void Server_ShiftKey();
	UFUNCTION(Server, UnReliable)
	virtual void Server_ShiftKeyComplete();
	UFUNCTION(NetMulticast, UnReliable)
	virtual void Multicast_ShiftKeyStart();
	UFUNCTION(NetMulticast, UnReliable)
	virtual void Multicast_ShiftKey();
	UFUNCTION(NetMulticast, UnReliable)
	virtual void Multicast_ShiftKeyComplete();

	UFUNCTION(Server, UnReliable)
	virtual void Server_SpaceKeyStart();
	UFUNCTION(NetMulticast, UnReliable)
	virtual void Multicast_SpaceKeyStart();
	UFUNCTION(Server, UnReliable)
	virtual void Server_SpaceKeyComplete();
	UFUNCTION(NetMulticast, UnReliable)
	virtual void Multicast_SpaceKeyComplete();

	UFUNCTION(Server, UnReliable)
	virtual void Server_EvadeKeyStart();
	UFUNCTION(NetMulticast, UnReliable)
	virtual void Multicast_EvadeKeyStart();


	UFUNCTION(BlueprintImplementableEvent)
	bool EnemyCameraCheck();

	UFUNCTION(BlueprintImplementableEvent)
	void EnemyCheck();


	//PlayerState
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UFsmComponent> FsmComp = nullptr;


private:
	void CameraInit();
	void TurnToEnemy(float DeltaTime);
	void LockOn();
	void LockOff();
	void SetupFsm();
	FVector CheckJumpPos();

	UFUNCTION(BlueprintCallable)
	void BlueprintChangeState(EPlayerState Value);

	UFUNCTION(BlueprintCallable)
	EPlayerState BlueprintGetCurState();

	UFUNCTION(Server, UnReliable)
	void Server_SetKeyDir(const FVector2D& Value);
	UFUNCTION(NetMulticast, UnReliable)
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
	FVector JumpStartPos = FVector::ZeroVector;
	FVector JumpEndPos = FVector::ZeroVector;
	float MaxJumpHeight = 600.f;
	float FallSpeed = 1000.f;
	FCollisionObjectQueryParams CheckParam;
	float GravityForce = 1000.f;
	float JumpRatio = 0.f;

	//Evade
	bool bEvadeKey = false;
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
	bool bLockOn = false;


	//Attack
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int CurComboCount = 0;
};
