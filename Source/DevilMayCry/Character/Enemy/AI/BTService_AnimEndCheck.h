// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_AnimEndCheck.generated.h"

/**
 * 
 */
UCLASS()
class DEVILMAYCRY_API UBTService_AnimEndCheck : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTService_AnimEndCheck();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
};
