// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "AreaSubSystem.generated.h"

UENUM()
enum class EPhase : uint8
{
	PHASE0	UMETA(DisplayName = "PHASE0"),
	PHASE1	UMETA(DisplayName = "PHASE1"),
	MAX,
};
ENUM_RANGE_BY_FIRST_AND_LAST(EPhase, EPhase::PHASE1, EPhase::MAX)

/**
 *
 */
UCLASS()
class DEVILMAYCRY_API UAreaSubSystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	struct Phase
	{
		friend class UAreaSubSystem;

		TObjectPtr<class AAreaTrigger> Trigger = nullptr;
		TObjectPtr<class AActor> Location = nullptr;

		TArray<TObjectPtr<class AAreaBlockingVolume>> BlockArray;
		TArray<TObjectPtr<class AStaticMeshActor>> MeshArray;
		TArray<TObjectPtr<class AEnemyBase>> EnemyArray;
	};

public:
	UAreaSubSystem();

	int32 GetCurPhase()
	{
		return static_cast<int32>(CurPhase);
	}
	void SwitchPhase(bool Value);

protected:
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;
	void FindPhase(UWorld* World);

private:
	TArray<Phase> PhaseArray;
	int32 CurPhase = static_cast<int32>(EPhase::PHASE0);
};
