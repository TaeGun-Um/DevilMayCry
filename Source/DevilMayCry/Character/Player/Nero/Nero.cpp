// Fill out your copyright notice in the Description page of Project Settings.


#include "Nero.h"

ANero::ANero()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ANero::BeginPlay()
{
	Super::BeginPlay();

	USkeletalMesh* SKM = LoadObject<USkeletalMesh>(nullptr, TEXT("/Script/Engine.SkeletalMesh'/Game/Asset/Character/Player/Nero/Mesh/Nero.Nero'"));

	if (SKM)
	{
		GetMesh()->SetSkeletalMesh(SKM);
		GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -90.f));
		GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
	}

}

void ANero::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ANero::LeftClick()
{
}

void ANero::RightClick()
{
}

void ANero::WheelClick()
{
}

void ANero::EKey()
{
}

void ANero::ShiftKey()
{
}

void ANero::SpaceKey()
{
}

