// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyPlayerState.h"
#include "Net/UnrealNetwork.h" // DOREPLIFETIME 매크로 사용

void ALobbyPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ALobbyPlayerState, bIsReady);
    DOREPLIFETIME(ALobbyPlayerState, bIsHost);
}

void ALobbyPlayerState::OnRep_IsReady()
{
    UE_LOG(LogTemp, Warning, TEXT("[PlayerState] Ready 상태 변경됨: %s"), bIsReady ? TEXT("Ready") : TEXT("Not Ready"));
}

void ALobbyPlayerState::OnRep_IsHost()
{
    UE_LOG(LogTemp, Warning, TEXT("[PlayerState] Host 상태 변경됨: %s"), bIsHost ? TEXT("Host") : TEXT("Client"));
}
