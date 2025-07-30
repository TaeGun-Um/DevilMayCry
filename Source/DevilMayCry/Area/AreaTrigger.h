// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerSphere.h"
#include "AreaTrigger.generated.h"

/**
 * 
 */
UCLASS()
class DEVILMAYCRY_API AAreaTrigger : public ATriggerSphere
{
	GENERATED_BODY()
	
public:
	AAreaTrigger();

protected:
	UFUNCTION()
	void OverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
};
