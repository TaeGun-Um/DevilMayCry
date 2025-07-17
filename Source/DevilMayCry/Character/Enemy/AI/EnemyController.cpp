// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Pawn.h"

AEnemyController::AEnemyController()
{

}

void AEnemyController::BeginPlay()
{
    Super::BeginPlay();

    if (EnemyBehaviorTree !=nullptr)
    {
        RunBehaviorTree(EnemyBehaviorTree);
    }
}

void AEnemyController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}
