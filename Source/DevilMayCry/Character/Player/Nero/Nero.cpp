// Fill out your copyright notice in the Description page of Project Settings.


#include "Nero.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "ArmComponent.h"
#include "SnatchActor.h"
#include "../../Enemy/EnemyBase.h"
#include "Components/CapsuleComponent.h"
#include "Engine/DamageEvents.h" 
#include "../../DamageType/GeneralDamageType.h"

ANero::ANero()
{
	PrimaryActorTick.bCanEverTick = true;
	
	ArmComp = CreateDefaultSubobject<UArmComponent>(TEXT("ArmComp"));

	TObjectPtr<USkeletalMesh> SKM = LoadObject<USkeletalMesh>(nullptr, TEXT("/Script/Engine.SkeletalMesh'/Game/Asset/Character/Player/Vergil/Mesh/Vergil.Vergil'"));

	if (SKM)
	{
		GetMesh()->SetSkeletalMesh(SKM);
		SwordCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("SwordCollision"));
		SwordCollision->SetupAttachment(GetMesh(), "L_Hand");
	}
}

void ANero::BeginPlay()
{
	Super::BeginPlay();

	Snatcher = GetWorld()->SpawnActor<ASnatchActor>(GetMesh()->GetBoneLocation("R_Forearm"), FRotator::ZeroRotator);
	Snatcher->SetOwnerActor(this);

	SwordCollision->OnComponentBeginOverlap.AddDynamic(this, &ANero::OverlapBegin);
	SwordCollision->SetGenerateOverlapEvents(false);
}

void ANero::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ANero::Attack()
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

void ANero::LockOnEvade()
{
	Evade();
}

void ANero::Jumping(float JumpHeight, FVector2D Dir, bool bBack)
{
	GetCharacterMovement()->GravityScale = 5.f;

	//중력 속도 = 중력 스케일 * 현재 중력
	float GravitySpeed = -GetWorld()->GetGravityZ() * GetCharacterMovement()->GravityScale;

	//수직 속도 = 루트(중력 * 높이 *2)
	float VerticalSpeed = FMath::Sqrt(GravitySpeed * JumpHeight * 2.f);

	//체공 시간 = 올라가는시간이 수직/중력 이니까 *2
	float AirTime =VerticalSpeed / GravitySpeed;

	if (!bBack)
	{
		AirTime *= 2.f;
	}

	//수평 속도 = 공중에 있는 동안 이동해야하니까 거리/체공시간
	float HorizontalSpeed = JumpDistance / AirTime;

	FVector LaunchVel;
	if (!bBack)
	{
		LaunchVel = FVector(Dir.X, Dir.Y, 0.f)* HorizontalSpeed + FVector::UpVector * VerticalSpeed;
	}
	else
	{
		LaunchVel = -GetActorForwardVector() * HorizontalSpeed + FVector::UpVector * VerticalSpeed;
	}

	//bool파라미터는 더해지는 가속도의 영향을 받을지
	LaunchCharacter(LaunchVel, true, true);
}

void ANero::ZKeyStart()
{
}

void ANero::ZKeyEnd()
{
	ArmComp->ChangeNextArm();
}
void ANero::Shift_WheelClick()
{
	Snatcher->StartFire(GetLockOnEnemy());
}

void ANero::WheelClick()
{
}

void ANero::RightClick()
{
	if (GetLockOnEnemy()==nullptr)
	{
		return;
	}

	FDamageEvent DamageEvent(UGeneralDamageType::StaticClass());

	GetLockOnEnemy()->TakeDamage(GunDamage, DamageEvent,GetController(),this);
}

void ANero::DamagedImpulse()
{
	DamagedImpulseAnim();
}

void ANero::Damagedgeneral()
{
	DamagedgeneralAnim();
}

void ANero::OverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this)
	{
		TObjectPtr<AEnemyBase> Enemy = Cast<AEnemyBase>(SweepResult.GetActor());
		if (Enemy!= nullptr)
		{			
			FDamageEvent DamageEvent(UGeneralDamageType::StaticClass());

			Enemy->TakeDamage(SwordDamage, DamageEvent, GetController(), this);
		}
	}
}

void ANero::ToggleCollision(bool Value)
{
	SwordCollision->SetGenerateOverlapEvents(Value);
}

