// Fill out your copyright notice in the Description page of Project Settings.


#include "UIAnimationInterface.h"

// Add default functionality here for any IUIAnimationInterface functions that are not pure virtual.

void IUIAnimationInterface::AnimInit()
{
	UE_LOG(LogTemp, Log, TEXT("Animation Setting Start | Class: %s"), *Cast<UObject>(this)->GetName());
}

void IUIAnimationInterface::PlayAnim()
{
	UE_LOG(LogTemp, Log, TEXT("Animation Start | Class: %s"), *Cast<UObject>(this)->GetName());
}
