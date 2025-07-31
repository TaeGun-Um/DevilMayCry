// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "AreaPortal.generated.h"

/**
 * 
 */
UCLASS()
class DEVILMAYCRY_API AAreaPortal : public ATriggerBox
{
	GENERATED_BODY()
	
public:
	AAreaPortal();

protected:
	UFUNCTION()
	void OverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:


};
