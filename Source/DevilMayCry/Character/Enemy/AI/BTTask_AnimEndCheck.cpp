// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_AnimEndCheck.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../EnemyBase.h"

UBTTask_AnimEndCheck::UBTTask_AnimEndCheck()
{
	NodeName = TEXT("AnimEndCheck");
}

EBTNodeResult::Type UBTTask_AnimEndCheck::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	TObjectPtr<UBlackboardComponent> BBComp = OwnerComp.GetBlackboardComponent();
	TObjectPtr<AEnemyBase> Owner = Cast<AEnemyBase>(BBComp->GetValueAsObject(TEXT("SelfActor")));

	UE_LOG(LogTemp, Warning, TEXT("progress"));
	if (Owner->GetMesh()->GetAnimInstance()->IsAnyMontagePlaying() == true)
	{
		return EBTNodeResult::InProgress;
	}
	
	return EBTNodeResult::Succeeded;
}
