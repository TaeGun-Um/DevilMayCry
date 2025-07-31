// Fill out your copyright notice in the Description page of Project Settings.


#include "UPnPSubsystem.h"
#include "HttpModule.h"
#include "Interfaces/IHttpResponse.h"
#include "Interfaces/IHttpRequest.h"

// miniupnpc
extern "C" {
#include "miniupnpc.h"
#include "upnpcommands.h"
}

void UUPnPSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);
    UE_LOG(LogTemp, Log, TEXT("[UUPnPSubsystem] Initialized. UPnP and IP systems are ready."));

    TryUPnPPortForward(7777); // Automatically attempts port forwarding when the game starts.
    RequestPublicIP(); // Request for public IP
}

void UUPnPSubsystem::Deinitialize()
{
    Super::Deinitialize();
    UE_LOG(LogTemp, Log, TEXT("[UUPnPSubsystem] Terminated."));
}

bool UUPnPSubsystem::TryUPnPPortForward(int32 Port)
{
    UPNPDev* devlist = upnpDiscover(2000, nullptr, nullptr, 0, 0, 2, nullptr);
    if (!devlist)
    {
        UE_LOG(LogTemp, Error, TEXT("[UPnPSubsystem] Router device not found."));
        return false;
    }

    UPNPUrls urls;
    IGDdatas data;
    char lanaddr[64];
    char wanaddr[64]; // ? Ãß°¡

    int r = UPNP_GetValidIGD(devlist, &urls, &data,
        lanaddr, sizeof(lanaddr),
        wanaddr, sizeof(wanaddr));
    freeUPNPDevlist(devlist);

    if (r == 0)
    {
        UE_LOG(LogTemp, Error, TEXT("[UPnPSubsystem] No UPnP IGD device."));
        return false;
    }

    UE_LOG(LogTemp, Log, TEXT("[UPnPSubsystem] Local LAN IP: %s"), *FString(lanaddr));
    UE_LOG(LogTemp, Log, TEXT("[UPnPSubsystem] Router WAN IP: %s"), *FString(wanaddr));

    char portStr[16];
    sprintf_s(portStr, sizeof(portStr), "%d", Port);

    int result = UPNP_AddPortMapping(urls.controlURL, data.first.servicetype,
        portStr, portStr, lanaddr, "UE5 Game", "UDP", nullptr, "0");

    if (result != UPNPCOMMAND_SUCCESS)
    {
        UE_LOG(LogTemp, Error, TEXT("[UPnPSubsystem] Port forwarding failed (code: %d)"), result);
        return false;
    }

    UE_LOG(LogTemp, Log, TEXT("[UPnPSubsystem] UPnP port forwarding succeeded: UDP %d"), Port);
    return true;
}

void UUPnPSubsystem::RequestPublicIP()
{
    FetchPublicIP();
}

void UUPnPSubsystem::FetchPublicIP()
{
    TSharedRef<IHttpRequest> Request = FHttpModule::Get().CreateRequest();
    Request->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr Req, FHttpResponsePtr Res, bool bSuccess)
        {
            if (bSuccess && Res.IsValid())
            {
                CachedPublicIP = Res->GetContentAsString();
                UE_LOG(LogTemp, Log, TEXT("[UPnPSubsystem] Public IP lookup successful: %s"), *CachedPublicIP);
            }
            else
            {
                CachedPublicIP = TEXT("0.0.0.0");
                UE_LOG(LogTemp, Error, TEXT("[UPnPSubsystem] Public IP lookup failed"));
            }
        });
    Request->SetURL("https://api.ipify.org");
    Request->SetVerb("GET");
    Request->ProcessRequest();
}