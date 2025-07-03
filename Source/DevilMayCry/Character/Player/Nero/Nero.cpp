// Fill out your copyright notice in the Description page of Project Settings.


#include "Nero.h"
#include "GameFramework/CharacterMovementComponent.h"

ANero::ANero()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ANero::BeginPlay()
{
	Super::BeginPlay();
}

void ANero::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ANero::DefaultAttack()
{
	UE_LOG(LogTemp, Warning, TEXT("Attack"));
	if (GetCharacterMovement()->IsFalling())
	{
		JumpAttackCombo();
	}
	else
	{
		RedQueenCombo();
	}
	
}

void ANero::DefaultEvade()
{
	UE_LOG(LogTemp, Warning, TEXT("Evade"));
	Evade();
}


