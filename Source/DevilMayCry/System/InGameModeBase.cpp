// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameModeBase.h"
#include "UObject/ConstructorHelpers.h"
#include "DevilMayCry/UI/HUD/InGameHUD.h"
#include "DevilMayCry/Helper/EndingSequenceManager.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/PlayerState.h"
#include "GameFramework/SpectatorPawn.h"
#include "Kismet/GameplayStatics.h"
// #include "OnlineSubsystemTypes.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "OnlineSubsystem.h"
// #include "OnlineSubsystemUtils.h"

AInGameModeBase::AInGameModeBase()
{
    // Default Pawn Class
    static ConstructorHelpers::FClassFinder<APawn> PawnBPClass(TEXT("/Game/Player/Nero/BP_Nero"));
    if (PawnBPClass.Succeeded())
    {
        DefaultPawnClass = PawnBPClass.Class;
    }

    // HUD Class
    HUDClass = AInGameHUD::StaticClass();

    // Player Controller Class
    static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/Input/BP_CharacterController"));
    if (PlayerControllerBPClass.Succeeded())
    {
        PlayerControllerClass = PlayerControllerBPClass.Class;
    }

    // Game State Class
    GameStateClass = AGameStateBase::StaticClass();

    // Player State Class
    PlayerStateClass = APlayerState::StaticClass();

    // Spectator Class
    SpectatorClass = ASpectatorPawn::StaticClass();
}

void AInGameModeBase::PostLogin(APlayerController* NewPlayer)
{
    Super::PostLogin(NewPlayer);

}

void AInGameModeBase::Logout(AController* Exiting)
{
    Super::Logout(Exiting);

}

void AInGameModeBase::BeginPlay()
{
    Super::BeginPlay();

}

void AInGameModeBase::EndingStart()
{
    // 엔딩 매니저 스폰
    AEndingSequenceManager* Manager = GetWorld()->SpawnActor<AEndingSequenceManager>();

    // 캡처 및 GameInstance 저장
    if (Manager)
    {
        Manager->CaptureAndStoreTexture();
    }

    ENetMode NetMode = GetWorld()->GetNetMode();

    if (NetMode == NM_Standalone)
    {
        // 스탠드얼론: 현재 방식 그대로
        UGameplayStatics::OpenLevel(GetWorld(), FName(TEXT("/Game/Scenes/EndingScene")));
    }
    else if (NetMode == NM_ListenServer)
    {
        // 서버: 세션 종료 후 서버 자신도 EndingScene으로
        if (IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get())
        {
            OnlineSub->GetSessionInterface()->DestroySession(NAME_GameSession);
        }

        // 서버의 클라이언트도 연결 해제 후 EndingScene으로 이동
        for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
        {
            if (APlayerController* PC = It->Get())
            {
                PC->ClientTravel("/Game/Scenes/EndingScene", TRAVEL_Absolute);
            }
        }

        // 서버도 EndingScene으로 전환
        UGameplayStatics::OpenLevel(GetWorld(), FName(TEXT("/Game/Scenes/EndingScene")));
    }
    else if (NetMode == NM_Client)
    {
        // 클라이언트: 이미 서버에서 ClientTravel 명령이 오므로 별도 처리 필요 없음
    }
}