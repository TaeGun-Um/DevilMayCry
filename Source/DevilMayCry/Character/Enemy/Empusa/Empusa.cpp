// Fill out your copyright notice in the Description page of Project Settings.


#include "Empusa.h"
#include "Components/CapsuleComponent.h"
#include "Engine/DamageEvents.h" 
#include "../../Player/ParentCharacter.h"
#include "../../DamageType/GeneralDamageType.h"

#include "GameFramework/Controller.h"
#include "AIController.h"
#include "../AI/EnemyController.h"

#include "DrawDebugHelpers.h"

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

		CollisionArray.SetNum(static_cast<uint8>(ECollisionSwitch::ALL));
		CollisionArray[static_cast<uint8>(ECollisionSwitch::LEFT)] = LeftHand;
		CollisionArray[static_cast<uint8>(ECollisionSwitch::RIGHT)] = RightHand;
	}

	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -90.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
}

void AEmpusa::BeginPlay()
{
	Super::BeginPlay();
	LeftHand->OnComponentBeginOverlap.AddDynamic(this, &AEmpusa::OverlapBegin);
	RightHand->OnComponentBeginOverlap.AddDynamic(this, &AEmpusa::OverlapBegin);
	ToggleCollision(false, ECollisionSwitch::ALL);
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
	if (Where == ECollisionSwitch::ALL)
	{
		for (auto Iter : CollisionArray)
		{
			Iter->SetGenerateOverlapEvents(Value);
		}
	}
	else
	{
		CollisionArray[static_cast<uint8>(Where)]->SetGenerateOverlapEvents(Value);
	}
}

void AEmpusa::OverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this)
	{
		TObjectPtr<AParentCharacter> Enemy = Cast<AParentCharacter>(SweepResult.GetActor());
		if (Enemy != nullptr)
		{
			FDamageEvent DamageEvent(UGeneralDamageType::StaticClass());

			Enemy->TakeDamage(AttackDamage, DamageEvent, GetController(), this);
		}
	}
}

void AEmpusa::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
