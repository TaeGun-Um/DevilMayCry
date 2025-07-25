// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/DamageEvents.h" 
#include "Components/ShapeComponent.h"
#include "../DamageType/DMC5DamageType.h"
#include "AIController.h"
#include "Kismet/KismetMathLibrary.h"
#include "../FsmComponent.h"
#include "../Player/ParentCharacter.h"

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

	AiController = Cast<AAIController>(GetController()); 
	AnimInst = Cast<UAnimInstance>(GetMesh()->GetAnimInstance());
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
	if (bCanPull&&CurHP <= 0.f)
	{
		bDead = true;
		CurDeadTime = MaxDeadTime;
	}
	if (DamageEvent.DamageTypeClass)
	{
		auto* DmgType = DamageEvent.DamageTypeClass->GetDefaultObject<UDMC5DamageType>();
		DmgType->TypeProcess(this,DamageCauser);
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

void AEnemyBase::TurnToTarget(float DeltaTime)
{
	if (TargetPlayer != nullptr)
	{
		FVector Direction = TargetPlayer->GetActorLocation() - GetActorLocation();

		//액터 방향 돌리기
		FRotator SmoothRot = FMath::RInterpTo(GetActorForwardVector().Rotation(), Direction.Rotation().GetNormalized(), DeltaTime, 1.f);
		SmoothRot.Roll = 0.f;
		SmoothRot.Pitch = 0.f;

		SetActorRotation(SmoothRot);
	}

}

void AEnemyBase::ToggleCollision(bool Value, uint8 Where)
{
}

bool AEnemyBase::LimitAngleOver(float Limit)
{
	FVector Forward = GetActorForwardVector();
	Forward.Z = 0;
	Forward.Normalize();

	FVector ToTarget = TargetPlayer->GetActorLocation() - GetActorLocation();
	ToTarget.Z = 0;
	ToTarget.Normalize();

	//내적으로 코사인세타 뽑기
	float Dot = FVector::DotProduct(Forward, ToTarget);
	//외적해서 Z축 뽑기
	float CrossZ = FVector::CrossProduct(Forward, ToTarget).Z;
	//아크탄젠트로 각도변환
	float Angle = FMath::Abs(FMath::RadiansToDegrees(FMath::Atan2(CrossZ, Dot)));

	if (Limit < Angle)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void AEnemyBase::TurnToActor(float DeltaTime)
{
	FRotator Rotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), TargetPlayer->GetActorLocation());
	Rotation.Pitch = 0;
	Rotation.Roll = 0;

	// 정속 보간
	Rotation = FMath::RInterpConstantTo(GetActorRotation(), Rotation, DeltaTime, 360.f);
	SetActorRotation(Rotation);

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
