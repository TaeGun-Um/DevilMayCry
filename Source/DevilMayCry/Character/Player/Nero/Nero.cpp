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

	//중력 속도 = 중력 스케일 * 현재 중력
	float GravitySpeed = -GetWorld()->GetGravityZ() * GetCharacterMovement()->GravityScale;

	//수직 속도 = 루트(중력 * 높이 *2)
	float VerticalSpeed = FMath::Sqrt(GravitySpeed * JumpHeight * 2.f);

	//체공 시간 = 올라가는시간이 수직/중력 이니까 *2
	float AirTime = 2.f * VerticalSpeed / GravitySpeed;

	//수평 속도 = 공중에 있는 동안 이동해야하니까 거리/체공시간
	float HorizontalSpeed = JumpDistance / AirTime;

	FVector LaunchVel = FVector(Dir.X, Dir.Y, 0.f) * HorizontalSpeed + FVector::UpVector * VerticalSpeed;

	//bool파라미터는 더해지는 가속도의 영향을 받을지
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
