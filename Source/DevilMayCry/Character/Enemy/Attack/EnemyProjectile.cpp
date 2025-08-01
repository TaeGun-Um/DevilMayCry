// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/DamageEvents.h" 

#include "../../Player/ParentCharacter.h"
#include "../../DamageType/GeneralDamageType.h"


// Sets default values
AEnemyProjectile::AEnemyProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));

	SphereCollision->InitSphereRadius(10.f);
	RootComponent = SphereCollision;

	SphereCollision->BodyInstance.SetCollisionProfileName(TEXT("Projectile"));



	ProjectileComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileComp->SetUpdatedComponent(SphereCollision);
	ProjectileComp->InitialSpeed = 4000.0f;
	ProjectileComp->MaxSpeed = 4000.0f;
	ProjectileComp->bRotationFollowsVelocity = true;
	ProjectileComp->bShouldBounce = false;
	ProjectileComp->ProjectileGravityScale = 0.0f;

	InitialLifeSpan = 3.f;
}

// Called when the game starts or when spawned
void AEnemyProjectile::BeginPlay()
{
	Super::BeginPlay();

	SphereCollision->OnComponentHit.AddDynamic(this, &AEnemyProjectile::OnHit);
}

// Called every frame
void AEnemyProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DrawDebugSphere(GetWorld(),GetActorLocation(), 10.f, 12, FColor::Red);

}

void AEnemyProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if (Hit.GetActor() && Hit.GetActor() != this)
	{
		TObjectPtr<AParentCharacter> Player = Cast<AParentCharacter>(Hit.GetActor());

		if (Player)
		{
			FDamageEvent DamageEvent(UGeneralDamageType::StaticClass());
			Player->TakeDamage(10.f, DamageEvent,nullptr,this);

			Destroy();
		}		
	}
}

void AEnemyProjectile::Fire(FVector Dir)
{
	ProjectileComp->Velocity = Dir * ProjectileComp->InitialSpeed;
}

