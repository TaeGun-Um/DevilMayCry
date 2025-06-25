// Fill out your copyright notice in the Description page of Project Settings.


#include "Empusa.h"
#include "Components/SkeletalMeshComponent.h"

AEmpusa::AEmpusa()
{

	SkmComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkmComp"));
}

void AEmpusa::BeginPlay()
{
	Super::BeginPlay();

	USkeletalMesh* SKM = LoadObject<USkeletalMesh>(nullptr, TEXT("/Script/Engine.SkeletalMesh'/Game/Asset/Character/Enemy/Empusa/mesh/em0100.em0100'"));

	if (SKM)
	{
		SkmComp->SetSkeletalMesh(SKM);
	}
	/*
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
