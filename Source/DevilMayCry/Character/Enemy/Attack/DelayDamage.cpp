// Fill out your copyright notice in the Description page of Project Settings.


#include "DelayDamage.h"
#include "Kismet/GameplayStatics.h"
#include "../../DamageType/GeneralDamageType.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundCue.h"


// Sets default values
ADelayDamage::ADelayDamage()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;


	SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp"));
	RootComponent = SceneComp;

	AudioComp = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComp"));
	AudioComp->SetupAttachment(RootComponent);
	AudioComp->bAutoActivate = false;
}

// Called when the game starts or when spawned
void ADelayDamage::BeginPlay()
{
	Super::BeginPlay();

	TObjectPtr<USoundCue> SC = LoadObject<USoundCue>(nullptr, TEXT("/Script/Engine.SoundCue'/Game/Asset/Sound/SFX/Cavaliere/Angelo_Rakurai_SFX.Angelo_Rakurai_SFX'"));

	if (SC)
	{
		AudioComp->SetSound(SC);
	}

	
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
			AudioComp->Play();

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

