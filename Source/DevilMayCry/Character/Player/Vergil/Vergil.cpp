// Fill out your copyright notice in the Description page of Project Settings.


#include "Vergil.h"

AVergil::AVergil()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AVergil::BeginPlay()
{
	Super::BeginPlay();
	USkeletalMesh* SKM = LoadObject<USkeletalMesh>(nullptr, TEXT("/Script/Engine.SkeletalMesh'/Game/Asset/Character/Player/Vergil/Mesh/Vergil.Vergil'"));

	if (SKM)
	{
		GetMesh()->SetSkeletalMesh(SKM);
	}


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
	}
}

void AVergil::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
