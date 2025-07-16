// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Attack.h"
#include "../EnemyBase.h"
#include "AIController.h"

UBTTask_Attack::UBTTask_Attack()
{
	NodeName = TEXT("Attack");
}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (OwnerComp.GetAIOwner() == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	TObjectPtr<AEnemyBase> Enemy = Cast<AEnemyBase>(OwnerComp.GetAIOwner()->GetPawn());

	if (Enemy == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	Enemy->RandomAttack();

	return EBTNodeResult::Succeeded;
}
