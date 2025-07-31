// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyHUD.h"
#include "DevilMayCry/UI/SelectWidget/SelectMultiplayWidget.h"
#include "DevilMayCry/UI/BasicWidget/BlackBGWidget.h"
#include "DevilMayCry/State/LobbyPlayerState.h"
#include "GameFramework/GameStateBase.h"
// #include "GameFramework/PlayerState.h"
#include "Kismet/GameplayStatics.h"

ALobbyHUD::ALobbyHUD()
{
    ClassSetting();
}

void ALobbyHUD::BeginPlay()
{
    Super::BeginPlay();
    VariableSetting();
    CreateFSM();

    ENetMode NetMode = GetWorld()->GetNetMode();

    if (GEngine)
    {
        FString Mode = NetMode == NM_ListenServer ? TEXT("ListenServer") :
            NetMode == NM_DedicatedServer ? TEXT("DedicatedServer") :
            NetMode == NM_Client ? TEXT("Client") :
            TEXT("Standalone");

        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("NetMode: %s"), *Mode));
    }

    LobbyPlayerController = GetOwningPlayerController();
    if (LobbyPlayerController)
    {
        FInputModeGameAndUI InputMode;
        InputMode.SetWidgetToFocus(MultiPlayWidgetInstance->TakeWidget());
        InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
        LobbyPlayerController->SetInputMode(InputMode);
        LobbyPlayerController->SetShowMouseCursor(true);
    }

    ////////////////// ¾ÈµÊ
    if (MultiPlayWidgetInstance)
    {
        if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
        {
            ALobbyPlayerState* PS = PC->GetPlayerState<ALobbyPlayerState>();
            if (PS && PS->bIsHost)
            {
                MultiPlayWidgetInstance->SetIsHost(true);
            }
            else
            {
                MultiPlayWidgetInstance->SetIsHost(false);
            }
        }

        //MultiPlayWidgetInstance->StartButtonHidden();
    }
}

void ALobbyHUD::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (IsValid(MultiFSM))
    {
        MultiFSM->Update(DeltaTime);
    }

    RefreshPlayerStates();
}

void ALobbyHUD::RefreshPlayerStates()
{
    UWorld* World = GetWorld();
    if (!World || !MultiPlayWidgetInstance) return;

    int32 Index = 0;

    for (APlayerState* PS : World->GetGameState()->PlayerArray)
    {
        if (ALobbyPlayerState* LPS = Cast<ALobbyPlayerState>(PS))
        {
            MultiPlayWidgetInstance->UpdatePlayerSlot(Index, true, LPS->bIsReady);
            Index++;
        }
    }

    // ³ª¸ÓÁö ½½·Ô ºñ¿ì±â
    for (int32 i = Index; i < 4; i++)
    {
        MultiPlayWidgetInstance->UpdatePlayerSlot(i, false, false);
    }

    MultiPlayWidgetInstance->UpdatePlayerCount();
}

void ALobbyHUD::ClassSetting()
{
    static ConstructorHelpers::FClassFinder<UUserWidget> BGBlackWidgetClassFinder(TEXT("/Game/UI/Basic/WBP_BlackBGWidget"));
    if (BGBlackWidgetClassFinder.Succeeded())
    {
        BGBlackWidgetClass = BGBlackWidgetClassFinder.Class;
    }

    static ConstructorHelpers::FClassFinder<UUserWidget> MultiWidgetClassFinder(TEXT("/Game/UI/Select/WBP_SelectMultiplayWidget"));
    if (MultiWidgetClassFinder.Succeeded())
    {
        MultiPlayWidgetClass = MultiWidgetClassFinder.Class;
    }

    EKeys::GetAllKeys(AllKeys);
}

void ALobbyHUD::VariableSetting()
{
    // ¼ø¼­´ë·Î CreateÇØ¾ß WidgetÀÌ À§¿¡ µ¤¾î ¾º¿öÁü
    BGBlackWidgetInstance = CreateWidget<UBlackBGWidget>(GetWorld(), BGBlackWidgetClass);
    BGBlackWidgetInstance->AddToViewport();

    MultiPlayWidgetInstance = CreateWidget<USelectMultiplayWidget>(GetWorld(), MultiPlayWidgetClass);
    MultiPlayWidgetInstance->AddToViewport();
    MultiPlayWidgetInstance->SetVisibility(ESlateVisibility::Hidden);
    MultiPlayWidgetInstance->SetLocalIP(LocalIP);
    MultiPlayWidgetInstance->SetPublicIP(PublicIP);
}

void ALobbyHUD::CreateFSM()
{
    if (nullptr != MultiFSM)
    {
        return;
    }

    MultiFSM = NewObject<UFSM>(this);

    // Logo ¡æ Title
    MultiFSM->CreateState({
        .StateValue = static_cast<int64>(EMultiFSMState::DISCONECT),
        .Start = [this]()  // Start
        {
            // MultiPlayWidgetInstance->SetVisibility(ESlateVisibility::Visible);
            // MultiPlayWidgetInstance->PlayFadeAnimation();
        },
        .Update = [this](float DeltaTime)  // Update
        {
            //if (true == MultiPlayWidgetInstance->GetIsChangeLocation2())
            //{

            //}

            //if (true == MultiPlayWidgetInstance->GetIsChangeMenu())
            //{
            //    MultiFSM->ChangeState(static_cast<int64>(EMultiFSMState::DISCONECT));
            //}

           for (const FKey& Key : AllKeys)
           {
               if (LobbyPlayerController->WasInputKeyJustPressed(Key))
               {
                   MultiFSM->ChangeState(static_cast<int64>(EMultiFSMState::MULTIPLAY));
                   break;
               }
           }
        },
        .End = [this]() // End
        {
            // MultiPlayWidgetInstance->SetVisibility(ESlateVisibility::Hidden);
            // MultiPlayWidgetInstance->SetIsChangeLocation2(false);
            // MultiPlayWidgetInstance->SetIsChangeMenu(false);
        }
        }
    );

    // Logo ¡æ Title
    MultiFSM->CreateState({
        .StateValue = static_cast<int64>(EMultiFSMState::MULTIPLAY),
        .Start = [this]()  // Start
        {
            MultiPlayWidgetInstance->SetVisibility(ESlateVisibility::Visible);
            MultiPlayWidgetInstance->PlayFadeAnimation();
        },
        .Update = [this](float DeltaTime)  // Update
        {
            if (true == MultiPlayWidgetInstance->GetIsChangeLocation2())
            {

            }

            if (true == MultiPlayWidgetInstance->GetIsChangeMenu())
            {
                // MultiFSM->ChangeState(static_cast<int64>(EMultiFSMState::DISCONECT));
            }
        },
        .End = [this]() // End
        {
            MultiPlayWidgetInstance->SetVisibility(ESlateVisibility::Hidden);
            MultiPlayWidgetInstance->SetIsChangeLocation2(false);
            MultiPlayWidgetInstance->SetIsChangeMenu(false);
        }
        }
    );

    MultiFSM->ChangeState(static_cast<int64>(EMultiFSMState::MULTIPLAY));
}