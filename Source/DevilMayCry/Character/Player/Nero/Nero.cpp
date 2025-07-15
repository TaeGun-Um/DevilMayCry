// Fill out your copyright notice in the Description page of Project Settings.


#include "Nero.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "ArmComponent.h"
#include "SnatchActor.h"
#include "../../Enemy/EnemyBase.h"

ANero::ANero()
{
	PrimaryActorTick.bCanEverTick = true;
	
	ArmComp = CreateDefaultSubobject<UArmComponent>(TEXT("ArmComp"));
	
}

void ANero::BeginPlay()
{
	Super::BeginPlay();

	Snatcher = GetWorld()->SpawnActor<ASnatchActor>(GetMesh()->GetBoneLocation("R_Forearm"), FRotator::ZeroRotator);
	Snatcher->SetOwnerActor(this);
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

	//�߷� �ӵ� = �߷� ������ * ���� �߷�
	float GravitySpeed = -GetWorld()->GetGravityZ() * GetCharacterMovement()->GravityScale;

	//���� �ӵ� = ��Ʈ(�߷� * ���� *2)
	float VerticalSpeed = FMath::Sqrt(GravitySpeed * JumpHeight * 2.f);

	//ü�� �ð� = �ö󰡴½ð��� ����/�߷� �̴ϱ� *2
	float AirTime =VerticalSpeed / GravitySpeed;

	if (!bBack)
	{
		AirTime *= 2.f;
	}

	//���� �ӵ� = ���߿� �ִ� ���� �̵��ؾ��ϴϱ� �Ÿ�/ü���ð�
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

	//bool�Ķ���ʹ� �������� ���ӵ��� ������ ������
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
