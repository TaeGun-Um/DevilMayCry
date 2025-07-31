// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGameModeBase.h"
#include "SocketSubsystem.h"
#include "Interfaces/IPv4/IPv4Address.h"
#include "DevilMayCry/UI/HUD/LobbyHUD.h"
#include "DevilMayCry/State/LobbyPlayerState.h"
#include "DevilMayCry/Network/UPnPSubsystem.h"
#include "GameFramework/GameStateBase.h"

ALobbyGameModeBase::ALobbyGameModeBase()
{
	HUDClass = ALobbyHUD::StaticClass();
	DefaultPawnClass = nullptr;
	bUseSeamlessTravel = false;

    //PlayerControllerClass = APlayerController_Lobby::StaticClass();
    //GameStateClass = AGameState_Lobby::StaticClass();
    PlayerStateClass = ALobbyPlayerState::StaticClass();
}

void ALobbyGameModeBase::PostLogin(APlayerController* NewPlayer)
{
    Super::PostLogin(NewPlayer);

    if (GetNumPlayers() > 4)
    {
        NewPlayer->ClientMessage(TEXT("The room is full"));
        NewPlayer->Destroy();
        return;
    }

    ConnectedPlayers++;

    // 첫 번째 플레이어가 Host
    if (ConnectedPlayers == 1)
    {
        //if (APlayerState_Lobby* PS = Cast<APlayerState_Lobby>(NewPlayer->PlayerState))
        //{
        //    PS->SetIsHost(true);
        //}
    }

    UE_LOG(LogTemp, Log, TEXT("Player Joined: %d"), ConnectedPlayers);

    // 모든 클라이언트에게 UI 갱신 명령
    for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
    {
        if (APlayerController* PC = It->Get())
        {
            if (ALobbyHUD* HUD = Cast<ALobbyHUD>(PC->GetHUD()))
            {
                HUD->RefreshPlayerStates();
            }
        }
    }
}

void ALobbyGameModeBase::Logout(AController* Exiting)
{
	Super::Logout(Exiting);
	ConnectedPlayers--;
}

void ALobbyGameModeBase::BeginPlay()
{
    Super::BeginPlay();

    UE_LOG(LogTemp, Warning, TEXT("[GameMode] LobbyScene Server Start, (ALobbyGameModeBase::BeginPlay)"));

    // 로컬 IP
    if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
    {
        if (ALobbyHUD* LobbyHUD = Cast<ALobbyHUD>(PC->GetHUD()))
        {
            FString LocalIP = GetHostIPAddress();
            LobbyHUD->SetLocalIP(LocalIP);

            if (GEngine)
            {
                GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Local IP: %s"), *LocalIP));
            }
        }
    }

    // 공인 IP

    // UUPnPSubsystem 가져오기
    if (UGameInstance* GI = GetGameInstance())
    {
        if (UUPnPSubsystem* UPnP = GI->GetSubsystem<UUPnPSubsystem>())
        {
            FString PublicIP = UPnP->GetCachedPublicIP(); // 초기엔 빈 값일 수 있음
            UE_LOG(LogTemp, Log, TEXT("현재 캐시된 공인 IP: %s"), *PublicIP);

            // HUD에 표시
            if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
            {
                if (ALobbyHUD* LobbyHUD = Cast<ALobbyHUD>(PC->GetHUD()))
                {
                    LobbyHUD->SetPublicIP(PublicIP);

                    if (GEngine)
                    {
                        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Public IP : %s"), *PublicIP));
                    }
                }
            }
        }
    }
}

FString ALobbyGameModeBase::GetHostIPAddress()
{
    bool bCanBind = false;

    // IPv4 주소 얻기
    TSharedRef<FInternetAddr> Addr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->GetLocalHostAddr(*GLog, bCanBind);
    FString IP = Addr->ToString(false); // 포트 제외: false

    return IP;
}

bool ALobbyGameModeBase::AllPlayersReady()
{
    for (APlayerState* PS : GameState->PlayerArray)
    {
        if (ALobbyPlayerState* LPS = Cast<ALobbyPlayerState>(PS))
        {
            if (!LPS->bIsReady)
            {
                return false;
            }
        }
    }
    return true;
}