// Fill out your copyright notice in the Description page of Project Settings.


#include "FSM.h"
#include "FSMState.h"

void UFSM::CreateState(const FStateParameter& _InParam)
{
	if (nullptr != FindState(_InParam.StateValue))
	{
		UE_LOG(LogTemp, Error, TEXT("State already exists: %d"), _InParam.StateValue);
		return;
	}

	FFSMState& NewState = AllStates.Add(_InParam.StateValue);
	NewState.StateValue = _InParam.StateValue;
	NewState.Start = _InParam.Start;
	NewState.Update = _InParam.Update;
	NewState.End = _InParam.End;
}

void UFSM::ChangeFunction(int64 _InState, TFunction<void()> _InStart, TFunction<void(float)> _InUpdate, TFunction<void()> _InEnd)
{
	FFSMState* State = FindState(_InState);
	if (State == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Trying to change non-existent state: %d"), _InState);
		return;
	}

	State->Start = _InStart;
	State->Update = _InUpdate;
	State->End = _InEnd;
}

void UFSM::ChangeState(int64 _InState)
{
	if (CurrentState && CurrentState->End)
	{
		CurrentState->End();
	}

	CurrentState = FindState(_InState);

	if (CurrentState == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Trying to change to non-existent state: %d"), _InState);
		return;
	}

	if (CurrentState->Start)
	{
		CurrentState->Start();
	}
}

void UFSM::Update(float _DeltaTime)
{
	if (CurrentState == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("FSM has no current state"));
		return;
	}

	if (CurrentState->Update)
	{
		CurrentState->Update(_DeltaTime);
	}
}

UFSM::FFSMState* UFSM::FindState(int64 _InState)
{
	return AllStates.Find(_InState);
}