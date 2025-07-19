// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FSM.generated.h"

USTRUCT()
struct FStateParameter
{
    GENERATED_BODY()

public:
    UPROPERTY()
    int64 StateValue;

    TFunction<void()> Start;
    TFunction<void(float)> Update;
    TFunction<void()> End;
};

/**
 * 
 */
UCLASS()
class DEVILMAYCRY_API UFSM : public UObject
{
	GENERATED_BODY()
	
public:
	// 상태 구조체
	struct FFSMState
	{
		int64 StateValue = -1;
		float CurStateTime = 0.0f;
		TFunction<void()> Start;
		TFunction<void(float)> Update;
		TFunction<void()> End;
	};

public:
	// API
	void CreateState(const FStateParameter& InParam);
	void ChangeFunction(int64 InState, TFunction<void()> InStart, TFunction<void(float)> InUpdate, TFunction<void()> InEnd);
	void ChangeState(int64 InState);
	void Update(float DeltaTime);

	UFUNCTION()
	bool IsValid() const { return CurrentState != nullptr; }

	UFUNCTION()
	int64 GetCurrentState() const { return CurrentState ? CurrentState->StateValue : -1; }

private:
	FFSMState* FindState(int64 InState);

private:
	TMap<int64, FFSMState> AllStates;
	FFSMState* CurrentState = nullptr;

};
