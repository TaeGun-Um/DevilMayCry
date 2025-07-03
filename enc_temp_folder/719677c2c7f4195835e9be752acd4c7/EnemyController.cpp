// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BehaviorTree.h"

AEnemyController::AEnemyController()
{
    ConstructorHelpers::FObjectFinder<UBehaviorTree> AIBehavior(TEXT("/Script/AIModule.BehaviorTree'/Game/Enemy/Empusa/BT_Empusa.BT_Empusa'"));

    if (AIBehavior.Succeeded())
    {
        EnemyBehaviorTree = AIBehavior.Object;
    }
}

void AEnemyController::BeginPlay()
{
}

void AEnemyController::Tick(float DeltaTime)
{
}

void AEnemyController::StateUpdate()
{
    switch (CurState)
    {
    case EAIState::Idle:
    {
        // ��� ���� ����
        break;
    }
    case EAIState::Patrol:
    {
        // ���� ���� ����
        break;
    }
    case EAIState::Run:
    {
        // ���� ���� ����
        break;
    }
    case EAIState::Attack:
    {
        // ���� ���� ����
        break;
    }
    }
}

void AEnemyController::TargetSearch(AActor* Actor, FAIStimulus AIStimulus)
{
    if (Actor->ActorHasTag("Player")&& AIStimulus.WasSuccessfullySensed())
    {
        GetBlackboardComponent()->SetValueAsBool("bFindTarget",true); 
        GetBlackboardComponent()->SetValueAsObject("TargetActor", Actor);        
    } 
}
