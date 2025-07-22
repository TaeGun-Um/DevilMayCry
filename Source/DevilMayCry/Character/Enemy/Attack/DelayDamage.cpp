// Fill out your copyright notice in the Description page of Project Settings.


#include "DelayDamage.h"
#include "Kismet/GameplayStatics.h"
#include "../../DamageType/GeneralDamageType.h"


// Sets default values
ADelayDamage::ADelayDamage()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADelayDamage::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ADelayDamage::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bActive)
	{
		CurDamageDelay -= DeltaTime;

		if (CurDamageDelay <=0.f)
		{
			UGameplayStatics::ApplyRadialDamage(
				this,
				Setter.Damage,
				Setter.Pos,
				Setter.Radius,
				Setter.DamageType,
				Setter.IgnoreList,
				this                			
			);

			DrawDebugSphere(GetWorld(), Setter.Pos, Setter.Radius, 12, FColor::Red, false, 2.f);

			bActive = false;
			CurDamageDelay = Setter.MaxDamageDelay;
		}
	}
}

