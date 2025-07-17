// Fill out your copyright notice in the Description page of Project Settings.


#include "Empusa.h"
#include "Components/CapsuleComponent.h"
#include "Engine/DamageEvents.h" 
#include "../../Player/ParentCharacter.h"
#include "../../DamageType/GeneralDamageType.h"
#include "../../DamageType/ImpulseDamageType.h"

#include "GameFramework/Controller.h"
#include "AIController.h"
#include "../AI/EnemyController.h"

AEmpusa::AEmpusa()
{
	//메시 세팅
	TObjectPtr<USkeletalMesh> SKM = LoadObject<USkeletalMesh>(nullptr, TEXT("/Script/Engine.SkeletalMesh'/Game/Asset/Character/Enemy/Empusa/mesh/em0100.em0100'"));

	if (SKM)
	{
		GetMesh()->SetSkeletalMesh(SKM);

		LeftHand = CreateDefaultSubobject<UCapsuleComponent>(TEXT("LeftHand"));
		LeftHand->SetupAttachment(GetMesh(), "L_Hand");
		RightHand = CreateDefaultSubobject<UCapsuleComponent>(TEXT("RightHand"));
		RightHand->SetupAttachment(GetMesh(), "R_Hand");
	}

	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -90.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
}

void AEmpusa::BeginPlay()
{
	Super::BeginPlay();


	LeftHand->OnComponentBeginOverlap.AddDynamic(this, &AEmpusa::OverlapBegin);
	RightHand->OnComponentBeginOverlap.AddDynamic(this, &AEmpusa::OverlapBegin);
}

void AEmpusa::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

void AEmpusa::ToggleCollision(bool Value, uint8 Where)
{
	ToggleCollision(Value, static_cast<ECollisionSwitch>(Where));
}

void AEmpusa::ToggleCollision(bool Value, ECollisionSwitch Where)
{
	switch (Where)
	{
	case ECollisionSwitch::NONE:
	{
	}
	case ECollisionSwitch::LEFT:
	{
		if (Value)
		{
			LeftHand->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		}
		else
		{
			LeftHand->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}
		break;
	}
	case ECollisionSwitch::RIGHT:
	{
		if (Value)
		{
			RightHand->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		}
		else
		{
			RightHand->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}
		break;
	}
	case ECollisionSwitch::ALL:
	{
		if (Value)
		{
			LeftHand->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
			RightHand->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		}
		else
		{
			LeftHand->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			RightHand->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}
		break;
	}
	}
}

void AEmpusa::OverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this)
	{
		TObjectPtr<AParentCharacter> Enemy = Cast<AParentCharacter>(SweepResult.GetActor());
		if (Enemy != nullptr)
		{
			FDamageEvent DamageEvent(UImpulseDamageType::StaticClass());

			Enemy->TakeDamage(AttackDamage, DamageEvent, GetController(), this);
		}
	}
}

void AEmpusa::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
