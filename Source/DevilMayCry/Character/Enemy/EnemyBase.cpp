// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/DamageEvents.h" 
#include "../DamageType/DMC5DamageType.h"

// Sets default values
AEnemyBase::AEnemyBase()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Tags.Add(TEXT("Enemy"));
}

// Called when the game starts or when spawned
void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DestroyCheck(DeltaTime);
}

float AEnemyBase::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float Dmg = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	CurHP -= std::min(Dmg, CurHP);


	//죽었을때 계속 때릴수 있어야함
	if (CurHP <= 0.f)
	{
		bDead = true;
		CurDeadTime = MaxDeadTime;
	}
	if (DamageEvent.DamageTypeClass)
	{
		auto* DmgType = DamageEvent.DamageTypeClass->GetDefaultObject<UDMC5DamageType>();
		DmgType->TypeProcess(this);

		DamagedAnimation(FVector::ZeroVector);
	}
	return Dmg;
}

void AEnemyBase::SetWalkSpeed(float Value)
{
	GetCharacterMovement()->MaxWalkSpeed = Value;
}

void AEnemyBase::DestroyCheck(float DeltaTime)
{
	if (bDead)
	{
		CurDeadTime -= DeltaTime;

		if (CurDeadTime <= 0.f)
		{
			Destroy();
		}
	}
}

void AEnemyBase::AirCheck(float DeltaTime)
{
	if (GetCharacterMovement()->IsFalling())
	{
		CurAirTime -= DeltaTime;

		if (CurAirTime <= 0.f)
		{
			GetCharacterMovement()->GravityScale = 1.f;
		}
	}
}

void AEnemyBase::ToggleCollision(bool Value,uint8 Where)
{
}

void AEnemyBase::DamagedGeneral()
{
}

void AEnemyBase::DamagedSnatch()
{
	if (!bCanPull)
	{
		return;
	}
	CurAirTime = MaxAirTime;
	GetCharacterMovement()->GravityScale = AirGravity;
}

void AEnemyBase::DamagedDefault()
{
	//공중에서 맞았을때 중력 조정용
	if (GetCharacterMovement()->IsFalling())
	{
		CurAirTime = MaxAirTime;
		GetCharacterMovement()->GravityScale = AirGravity;
	}
}
