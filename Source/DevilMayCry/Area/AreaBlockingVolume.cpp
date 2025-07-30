// Fill out your copyright notice in the Description page of Project Settings.


#include "AreaBlockingVolume.h"
#include "Components/BrushComponent.h"

AAreaBlockingVolume::AAreaBlockingVolume()
{
	Tags.Add(TEXT("AREA"));
}

void AAreaBlockingVolume::PostInitializeComponents()
{
    Super::PostInitializeComponents();
}

#if WITH_EDITOR
void AAreaBlockingVolume::LoadedFromAnotherClass(const FName& OldClassName)
{
	// Super::LoadedFromAnotherClass(OldClassName);

}

void AAreaBlockingVolume::PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedEvent)
{
	// Super::PostEditChangeChainProperty(PropertyChangedEvent);

}
#endif