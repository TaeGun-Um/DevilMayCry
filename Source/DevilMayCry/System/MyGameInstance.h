// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

UENUM(BlueprintType)
enum class EMapChangeValue : uint8
{
	LOCATION2,
	LOCATION11,
	NONE
};

/**
 * 
 */
UCLASS()
class DEVILMAYCRY_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	void SetMapChangeValue(EMapChangeValue _Value) { MapChangeValue = _Value; }

	UPROPERTY(BlueprintReadWrite) // Ending 캡쳐본 저장용
	TObjectPtr<class UTexture2D> CapturedEndingTexture;

	UPROPERTY(BlueprintReadWrite) // LoadingScene 전환용
	EMapChangeValue MapChangeValue = EMapChangeValue::NONE;

};
