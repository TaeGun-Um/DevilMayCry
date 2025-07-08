// Fill out your copyright notice in the Description page of Project Settings.


#include "Nero.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "ArmComponent.h"

ANero::ANero()
{
	PrimaryActorTick.bCanEverTick = true;
	
	ArmComp = CreateDefaultSubobject<UArmComponent>(TEXT("ArmComp"));
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
	Evade();
}

void ANero::DefaultJump(float JumpHeight, FVector2D Dir)
{
	GetCharacterMovement()->GravityScale = 5.f;

	//�߷� �ӵ� = �߷� ������ * ���� �߷�
	float GravitySpeed = -GetWorld()->GetGravityZ() * GetCharacterMovement()->GravityScale;

	//���� �ӵ� = ��Ʈ(�߷� * ���� *2)
	float VerticalSpeed = FMath::Sqrt(GravitySpeed * JumpHeight * 2.f);

	//ü�� �ð� = �ö󰡴½ð��� ����/�߷� �̴ϱ� *2
	float AirTime = 2.f * VerticalSpeed / GravitySpeed;

	//���� �ӵ� = ���߿� �ִ� ���� �̵��ؾ��ϴϱ� �Ÿ�/ü���ð�
	float HorizontalSpeed = JumpDistance / AirTime;

	FVector LaunchVel = FVector(Dir.X, Dir.Y, 0.f) * HorizontalSpeed + FVector::UpVector * VerticalSpeed;

	//bool�Ķ���ʹ� �������� ���ӵ��� ������ ������
	LaunchCharacter(LaunchVel, true, true);
}

void ANero::DefaultZKeyStart()
{
	ArmChangeAttack();
}

void ANero::DefaultZKeyEnd()
{
	ArmComp->ChangeNextArm();
}
