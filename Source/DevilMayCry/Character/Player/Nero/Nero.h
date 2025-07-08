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
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void DefaultAttack() override;
	virtual void DefaultEvade() override;
	virtual void DefaultJump(float JumpHeight, FVector2D Dir) override;
	virtual void DefaultZKeyStart();
	virtual void DefaultZKeyEnd();

	UFUNCTION(BlueprintImplementableEvent)
	void RedQueenCombo();

	UFUNCTION(BlueprintImplementableEvent)
	void JumpAttackCombo();

	UFUNCTION(BlueprintImplementableEvent)
	void Evade();

	UFUNCTION(BlueprintImplementableEvent)
	void ArmChangeAttack();


	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UArmComponent> ArmComp = nullptr;
private:

};
