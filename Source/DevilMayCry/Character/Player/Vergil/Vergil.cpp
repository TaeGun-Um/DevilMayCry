// Fill out your copyright notice in the Description page of Project Settings.


#include "Vergil.h"

AVergil::AVergil()
{
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -90.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
}

void AVergil::BeginPlay()
{
	Super::BeginPlay();
	USkeletalMesh* SKM = LoadObject<USkeletalMesh>(nullptr, TEXT("/Script/Engine.SkeletalMesh'/Game/Asset/Character/Player/Vergil/Mesh/Vergil.Vergil'"));

	if (SKM)
	{
		GetMesh()->SetSkeletalMesh(SKM);
	}
}

void AVergil::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AVergil::LeftClick()
{
}

void AVergil::RightClick()
{
}

void AVergil::WheelClick()
{
}

void AVergil::EKey()
{
}

void AVergil::ShiftKey()
{
}

void AVergil::SpaceKey()
{
}
