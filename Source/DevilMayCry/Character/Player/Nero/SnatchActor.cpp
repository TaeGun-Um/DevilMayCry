// Fill out your copyright notice in the Description page of Project Settings.


#include "SnatchActor.h"
#include "Components/SphereComponent.h"
#include "DrawDebugHelpers.h"
#include "../../Enemy/EnemyBase.h"
#include "../ParentCharacter.h"


// Sets default values
ASnatchActor::ASnatchActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SetRootComponent(SphereComp);

	SphereComp->SetSphereRadius(ColRadius);
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ASnatchActor::OnSphereOverlap);
}

// Called when the game starts or when spawned
void ASnatchActor::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ASnatchActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//ui 만들어지기 전까지 사용할 락온 디버깅용 구체
	DrawDebugSphere(GetWorld(), GetActorLocation(), ColRadius, 12, FColor::Blue);

	Launch(DeltaTime);
}

void ASnatchActor::StartFire(TObjectPtr<class AEnemyBase> Enemy)
{
	SphereComp->SetActive(true);

	SnatchEnemy = Enemy;
	SetActorLocation(OwnerActor->GetActorLocation());
	bFire = true; 
	bPullActor = false;
	FVector Temp;

	if (SnatchEnemy!= nullptr)
	{
		Temp = (SnatchEnemy->GetActorLocation() - GetActorLocation()) ;
		Temp.Normalize();
	}
	else
	{
		Temp = OwnerActor->GetMesh()->GetRightVector();
	}

	FirePos = GetActorLocation() + Temp * MaxLength;
	StartPos = GetActorLocation();
	Ratio = 0.f;
}


void ASnatchActor::Launch(float DeltaTime)
{
	if (bFire && !bPullActor)
	{
		Ratio = FMath::Clamp(Ratio += DeltaTime * SnatchSpeed, 0.f, 1.f);
		FVector Temp = FMath::Lerp(StartPos, FirePos, Ratio);

		FHitResult Hit;
		SetActorLocation(Temp);		
	}

	else if (bFire && bPullActor)
	{
		Ratio = FMath::Clamp(Ratio -= DeltaTime * SnatchSpeed, 0.f, 1.f);
		FVector Temp = FMath::Lerp(StartPos, FirePos, Ratio);

		SetActorLocation(Temp);
		if (SnatchEnemy != nullptr)
		{
			SnatchEnemy->SetActorLocation(Temp);
		}

		if (Ratio == 0.f)
		{
			bPullActor = false;
			bFire = false;
			SnatchEnemy = nullptr;

			SphereComp->SetActive(false);
		}
	}
}

void ASnatchActor::OnSphereOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this)
	{
		if (SweepResult.GetActor() == SnatchEnemy)
		{
			bPullActor = true;
			StartPos = OwnerActor->GetActorLocation() + OwnerActor->GetMesh()->GetRightVector() * PullDistance;
		}
	}
}

