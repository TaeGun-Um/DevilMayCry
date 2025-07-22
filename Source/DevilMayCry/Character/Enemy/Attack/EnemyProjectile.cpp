// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "DrawDebugHelpers.h"

// Sets default values
AEnemyProjectile::AEnemyProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));

	SphereCollision->InitSphereRadius(10.0f);
	RootComponent = SphereCollision;

	//SphereCollision->BodyInstance.SetCollisionProfileName(TEXT(""));



	ProjectileComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileComp->SetUpdatedComponent(SphereCollision);
	ProjectileComp->InitialSpeed = 3000.0f;
	ProjectileComp->MaxSpeed = 3000.0f;
	ProjectileComp->bRotationFollowsVelocity = true;
	ProjectileComp->bShouldBounce = false;
	ProjectileComp->ProjectileGravityScale = 0.0f;

	InitialLifeSpan = 3.f;
}

// Called when the game starts or when spawned
void AEnemyProjectile::BeginPlay()
{
	Super::BeginPlay();

	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, );
}

// Called every frame
void AEnemyProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DrawDebugSphere(GetWorld(),GetActorLocation(), 10.f, 12, FColor::Red);

}

void AEnemyProjectile::Fire(FVector Dir)
{
	ProjectileComp->Velocity = Dir * ProjectileComp->InitialSpeed;
}

