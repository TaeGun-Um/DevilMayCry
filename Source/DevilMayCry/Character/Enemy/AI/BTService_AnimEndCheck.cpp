// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_AnimEndCheck.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../EnemyBase.h"

UBTService_AnimEndCheck::UBTService_AnimEndCheck()
{
	NodeName = TEXT("AnimEndCheck");
}

void UBTService_AnimEndCheck::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	TObjectPtr<UBlackboardComponent> BBComp = OwnerComp.GetBlackboardComponent();
	TObjectPtr<AEnemyBase> Owner = Cast<AEnemyBase>(BBComp->GetValueAsObject(TEXT("SelfActor")));

	OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), Owner->GetMesh()->GetAnimInstance()->IsAnyMontagePlaying());
}
