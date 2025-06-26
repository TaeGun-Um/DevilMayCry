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
    AIPerceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception"));

    SetPerceptionComponent(*AIPerceptionComp);

    TObjectPtr<UAISenseConfig_Sight> SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
    SightConfig->SightRadius = 800.f;
    SightConfig->LoseSightRadius = 1200.f;
    SightConfig->PeripheralVisionAngleDegrees = 60.f;
    SightConfig->AutoSuccessRangeFromLastSeenLocation = -1.f;

    SightConfig->DetectionByAffiliation.bDetectEnemies = true;
    SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
    SightConfig->DetectionByAffiliation.bDetectFriendlies = false;

    AIPerceptionComp->ConfigureSense(*SightConfig);
    AIPerceptionComp->SetDominantSense(SightConfig->GetSenseImplementation());
    AIPerceptionComp->OnTargetPerceptionUpdated.AddDynamic(this, &AEnemyController::TargetSearch);

    RunBehaviorTree(EnemyBehaviorTree);
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
        // 대기 상태 로직
        break;
    }
    case EAIState::Patrol:
    {
        // 순찰 상태 로직
        break;
    }
    case EAIState::Run:
    {
        // 추적 상태 로직
        break;
    }
    case EAIState::Attack:
    {
        // 공격 상태 로직
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
