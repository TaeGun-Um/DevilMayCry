// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "UPnPSubsystem.generated.h"

/**
 * UUPnPSubsystem
 * - Attempt UPnP port forwarding when starting the game
 * - Automatic public IP lookup
 * - Easily accessible from Blueprint and C++
 */
UCLASS()
class DEVILMAYCRY_API UUPnPSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
    /** Called on initialization */
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;

    /** Call on exit */
    virtual void Deinitialize() override;

    /** Attempt UPnP port forwarding */
    UFUNCTION(BlueprintCallable, Category = "Network")
    bool TryUPnPPortForward(int32 Port);

    /** Request public IP (returned as callback) */
    UFUNCTION(BlueprintCallable, Category = "Network")
    void RequestPublicIP();

    /** Get public IP (last viewed value) */
    UFUNCTION(BlueprintCallable, Category = "Network")
    FString GetCachedPublicIP() const { return CachedPublicIP; }

private:
    FString CachedPublicIP;

    /** Internal use: Lookup public IP address with HTTP request */
    void FetchPublicIP();
};
