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

void ANero::Server_LeftClick_Implementation()
{
	Multicast_LeftClick();
}

void ANero::Multicast_LeftClick_Implementation()
{
	if (GetCharacterMovement()->IsFalling())
	{
		JumpAttackCombo();
	}
	else
	{
		RedQueenCombo();
	}
}

void ANero::Server_EvadeKeyStart_Implementation()
{
	Multicast_EvadeKeyStart();
}

void ANero::Multicast_EvadeKeyStart_Implementation()
{
	Evade();
}

