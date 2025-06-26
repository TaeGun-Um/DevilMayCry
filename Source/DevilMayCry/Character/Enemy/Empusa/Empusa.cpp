// Fill out your copyright notice in the Description page of Project Settings.


#include "Empusa.h"
#include "GameFramework/Controller.h"
#include "AIController.h"
#include "../EnemyController.h"

AEmpusa::AEmpusa()
{
	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -90.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));


	ConstructorHelpers::FObjectFinder<AController> AIController(TEXT("/Script/Engine.Blueprint'/Game/Enemy/BP_EnemyController.BP_EnemyController'"));

	//AI컨트롤러 세팅
	//TObjectPtr<UClass> AIController = LoadObject<UClass>(nullptr, TEXT("/Script/Engine.Blueprint'/Game/Enemy/BP_EnemyController.BP_EnemyController'"));

	if (AIController.Succeeded())
	{
		AIControllerClass = AIController.Object.GetClass();
		AutoPossessAI = EAutoPossessAI::Spawned;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController Fail"));
	}
	//AIControllerClass = AEnemyController
}

void AEmpusa::BeginPlay()
{
	Super::BeginPlay();

	//메시 세팅
	TObjectPtr<USkeletalMesh> SKM = LoadObject<USkeletalMesh>(nullptr, TEXT("/Script/Engine.SkeletalMesh'/Game/Asset/Character/Enemy/Empusa/mesh/em0100.em0100'"));

	if (SKM)
	{
		GetMesh()->SetSkeletalMesh(SKM);
	}


	/*
	//애니메이션 세팅
	UAnimBlueprint* AnimSeq = LoadObject<UAnimBlueprint>(nullptr, TEXT("/Script/Engine.AnimBlueprint'/Game/Player/Nero/ABP_Nero.ABP_Nero'"));

	if (AnimSeq)
	{
		GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
		GetMesh()->SetAnimInstanceClass(*AnimSeq->GeneratedClass);
		UE_LOG(LogTemp, Warning, TEXT("Anim success"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Anim Fail"));
	}*/


}

void AEmpusa::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

void AEmpusa::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
