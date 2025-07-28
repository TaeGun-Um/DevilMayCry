// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "LobbyPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class DEVILMAYCRY_API ALobbyPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
    UPROPERTY(ReplicatedUsing = OnRep_IsReady)
    bool bIsReady = false;

    UPROPERTY(ReplicatedUsing = OnRep_IsHost)
    bool bIsHost = false;

    UFUNCTION(Server, Reliable)
    void ServerSetReady(bool _bIsNewReady);

    void SetIsHost(bool NewValue);

protected:
    virtual void BeginPlay() override;
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    UFUNCTION()
    void OnRep_IsReady();

    UFUNCTION()
    void OnRep_IsHost();
};
