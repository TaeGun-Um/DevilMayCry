// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_AnimEndCheck.generated.h"

/**
 * 
 */
UCLASS()
class DEVILMAYCRY_API UBTTask_AnimEndCheck : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_AnimEndCheck();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
};
