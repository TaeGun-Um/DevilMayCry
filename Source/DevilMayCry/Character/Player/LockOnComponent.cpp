// Fill out your copyright notice in the Description page of Project Settings.


#include "LockOnComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "DrawDebugHelpers.h"
#include "ParentCharacter.h"
#include "../Enemy/EnemyBase.h"

// Sets default values for this component's properties
ULockOnComponent::ULockOnComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

   
}


// Called when the game starts
void ULockOnComponent::BeginPlay()
{
	Super::BeginPlay();
    Owner = Cast<AParentCharacter>(GetOwner());
}


// Called every frame
void ULockOnComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (IsValid(LockOnEnemy))
    {
        FRotator Look = UKismetMathLibrary::FindLookAtRotation(Owner->GetActorLocation(), LockOnEnemy->GetActorLocation());
    
        Owner->GetController()->SetControlRotation(Look);
    
        UE_LOG(LogTemp, Warning, TEXT("Test"));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Invalid"));
        
    }
}

