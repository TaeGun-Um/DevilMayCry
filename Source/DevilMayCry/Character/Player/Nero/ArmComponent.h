// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ArmComponent.generated.h"


UENUM(BlueprintType)
enum class EArmType :uint8
{
	OVERTURE		UMETA(DisplayName = "OVERTURE"),
	GERBERA			UMETA(DisplayName = "GERBERA"),
	//BUSTER			UMETA(DisplayName = "BUSTER"),
	MAX				UMETA(Hidden),
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DEVILMAYCRY_API UArmComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UArmComponent();

public:
	void ChangeNextArm();

	UFUNCTION(BlueprintCallable)
	EArmType GetCurArmType() const
	{
		return CurArmType;
	}

	UFUNCTION(BlueprintCallable)
	class USkeletalMeshComponent* GetArmMesh() const
	{
		return SkmComp;
	}

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		

private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USkeletalMeshComponent> SkmComp = nullptr;
	TArray<class USkeletalMesh*> arrDevilBreaker;
	EArmType CurArmType = EArmType::OVERTURE;

	TObjectPtr<class AParentCharacter> Owner = nullptr;
};
