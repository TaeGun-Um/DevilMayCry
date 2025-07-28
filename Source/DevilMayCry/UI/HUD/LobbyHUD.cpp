// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyHUD.h"
#include "DevilMayCry/UI/SelectWidget/SelectMultiplayWidget.h"
#include "DevilMayCry/UI/BasicWidget/BlackBGWidget.h"
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
}

void ALobbyHUD::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (IsValid(MultiFSM))
    {
        MultiFSM->Update(DeltaTime);
    }
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
    MultiPlayWidgetInstance->SetHostIP(HostIP);

    if (LobbyPlayerController)
    {
        LobbyPlayerController->SetShowMouseCursor(true);

        FInputModeGameAndUI InputMode;
        InputMode.SetWidgetToFocus(MultiPlayWidgetInstance->TakeWidget());
        InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
        LobbyPlayerController->SetInputMode(InputMode);
        LobbyPlayerController->SetShowMouseCursor(true);
    }
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