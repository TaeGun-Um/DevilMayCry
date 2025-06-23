// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ParentCharacter.generated.h"

UCLASS(Abstract)
class AParentCharacter : public ACharacter
{
	GENERATED_BODY()

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


protected:
	virtual void LeftClick()	PURE_VIRTUAL(AParentCharacter::LeftClick, ;);
	virtual void RightClick()	PURE_VIRTUAL(AParentCharacter::RightClick, ;);
	virtual void WheelClick()	PURE_VIRTUAL(AParentCharacter::WheelClick, ;);
	virtual void EKey()			PURE_VIRTUAL(AParentCharacter::EKey, ;);
	virtual void ShiftKey()		PURE_VIRTUAL(AParentCharacter::ShiftKey, ;);
	virtual void SpaceKey()		PURE_VIRTUAL(AParentCharacter::SpaceKey, ;);

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UCameraComponent> CameraComp;

};
