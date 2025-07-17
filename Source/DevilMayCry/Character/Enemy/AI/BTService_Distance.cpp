// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_Distance.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../EnemyBase.h"

UBTService_Distance::UBTService_Distance()
{
	NodeName = TEXT("Distance");
}

void UBTService_Distance::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	
	TObjectPtr<UBlackboardComponent> BBComp = OwnerComp.GetBlackboardComponent();
	TObjectPtr<AActor> Owner = Cast<AActor>(BBComp->GetValueAsObject(TEXT("SelfActor")));
	TObjectPtr<AActor> Target = Cast<AActor>(BBComp->GetValueAsObject(TEXT("TargetActor")));

	if (Owner ==nullptr || Target == nullptr)
	{
		return;
	}

	float Distance = (Owner->GetActorLocation() - Target->GetActorLocation()).Length();

	OwnerComp.GetBlackboardComponent()->SetValueAsFloat(GetSelectedBlackboardKey(), Distance);
}
