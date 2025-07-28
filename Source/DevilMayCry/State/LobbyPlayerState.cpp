// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyPlayerState.h"
#include "Net/UnrealNetwork.h" // DOREPLIFETIME 매크로 사용
#include "DevilMayCry/UI/HUD/LobbyHUD.h"

void ALobbyPlayerState::BeginPlay()
{
    Super::BeginPlay();

    // 최초 접속 시 현재 Ready 상태 UI 반영
    //if (APlayerController* PC = Cast<APlayerController>(GetOwner()))
    //{
    //    if (UWorld* World = PC->GetWorld())
    //    {
    //        if (ALobbyHUD* HUD = Cast<ALobbyHUD>(PC->GetHUD()))
    //        {
    //            HUD->RefreshPlayerStates();
    //        }
    //    }
    //}
}

void ALobbyPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ALobbyPlayerState, bIsReady);
    DOREPLIFETIME(ALobbyPlayerState, bIsHost);
}

void ALobbyPlayerState::OnRep_IsReady()
{
    UE_LOG(LogTemp, Warning, TEXT("[PlayerState] Ready State Changed: %s"), bIsReady ? TEXT("Ready") : TEXT("Not Ready"));

    if (APlayerController* PC = Cast<APlayerController>(GetOwner()))
    {
        if (UWorld* World = PC->GetWorld())
        {
            if (ALobbyHUD* HUD = Cast<ALobbyHUD>(PC->GetHUD()))
            {
                HUD->RefreshPlayerStates(); // HUD에서 위젯 업데이트
            }
        }
    }
}

void ALobbyPlayerState::SetIsHost(bool NewValue)
{
    if (HasAuthority())
    {
        bIsHost = NewValue;
        OnRep_IsHost();
    }
}

void ALobbyPlayerState::ServerSetReady_Implementation(bool _bIsNewReady)
{
    bIsReady = _bIsNewReady;
    OnRep_IsReady();
}

void ALobbyPlayerState::OnRep_IsHost()
{
    UE_LOG(LogTemp, Warning, TEXT("[PlayerState] Host State Changed: %s"), bIsHost ? TEXT("Host") : TEXT("Client"));
}
