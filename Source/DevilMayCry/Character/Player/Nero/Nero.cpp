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

void ANero::Server_LeftClick_Implementation()
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

void ANero::Server_Evade_Implementation()
{
	AParentCharacter::Server_Evade_Implementation();
	FVector2D Dir = GetMoveDir();
}

void ANero::Multicast_Evade_Implementation()
{
	AParentCharacter::Multicast_Evade_Implementation();
	FVector2D Dir = GetMoveDir();
}

