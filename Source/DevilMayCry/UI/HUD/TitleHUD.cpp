// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleHUD.h"
#include "Blueprint/UserWidget.h"
#include "DevilMayCry/UI/BasicWidget/BlackBGWidget.h"
#include "DevilMayCry/UI/TitleWidget/TitleLogoWidget.h"
#include "DevilMayCry/UI/TitleWidget/TitleWidget.h"
#include "DevilMayCry/UI/SelectWidget/SelectCharacterWidget.h"
#include "DevilMayCry/UI/SelectWidget/SelectMenuWidget.h"
#include "Kismet/GameplayStatics.h"

ATitleHUD::ATitleHUD()
{
    ClassSetting();
}

void ATitleHUD::BeginPlay()
{
    Super::BeginPlay();
    VariableSetting();
    CreateFSM();
}

void ATitleHUD::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    TitleFSM->Update(DeltaTime);
}

// BG Animation 바인딩용
void ATitleHUD::TitleDelayEvent()
{
    TitleFSM->ChangeState(static_cast<int64>(ETitleFSMState::TITLE));
}

void ATitleHUD::CreateFSM()
{
    if (nullptr != TitleFSM)
    {
        return;
    }

    TitleFSM = NewObject<UFSM>(this);

    // Logo → Title
    TitleFSM->CreateState({
        .StateValue = static_cast<int64>(ETitleFSMState::LOGO),
        .Start = [this]()  // Start
        {
            TitleLogoWidgetInstance->SetVisibility(ESlateVisibility::Visible);
            TitleLogoWidgetInstance->PlayFadeAnimation();
        },
        .Update = [this](float DeltaTime)  // Update
        {
            if (false == bIsLogoHandled && true == TitleLogoWidgetInstance->IsAnimationEnd())
            {
                bIsLogoHandled = true;
                GetWorldTimerManager().SetTimer(TitleLogoAnimEndHandle, this, &ATitleHUD::TitleDelayEvent, 1.0f, false);
            }
        },
        .End = [this]() // End
        {
            TitleLogoWidgetInstance->SetVisibility(ESlateVisibility::Hidden);
            bIsLogoHandled = false;
        }
        }
    );

    // Character
    TitleFSM->CreateState({
        .StateValue = static_cast<int64>(ETitleFSMState::TITLE),
        .Start = [this]()  // Start
        {
            TitleWidgetInstance->SetVisibility(ESlateVisibility::Visible);
            TitleWidgetInstance->PlayFadeAnimation();
            TitleWidgetInstance->PlayBlinkAnimation();
        },
        .Update = [this](float DeltaTime)  // Update
        {
            if (true == TitleWidgetInstance->GetIsEnd())
            {
                TitleFSM->ChangeState(static_cast<int64>(ETitleFSMState::CHARACTERSELECT));
            }

            if (false == bIsAnykeyHandled)
            {
                for (const FKey& Key : AllKeys)
                {
                    if (HUDPlayerController->WasInputKeyJustPressed(Key))
                    {
                        bIsAnykeyHandled = true;
                        TitleWidgetInstance->StopBlinkAnimation();
                        TitleWidgetInstance->SetVisibileButton();
                        break;
                    }
                }
            }
            else
            {
                if (true == TitleWidgetInstance->IsButtonHovered()) // 마우스 호버링 중에는 작동 X
                {
                    return;
                }
                else // 마우스 언호버링 중에 작동(키보드 입력)
                {
                    ETitleMenuType TypeValue = TitleWidgetInstance->GetMenuType();
                    switch (TypeValue)
                    {
                    case ETitleMenuType::MainMenu:
                    {
                        if (HUDPlayerController->WasInputKeyJustPressed(EKeys::Enter))
                        {
                            TitleWidgetInstance->StartButtonClicked();
                        }
                        else if (HUDPlayerController->WasInputKeyJustPressed(EKeys::Up) ||
                            HUDPlayerController->WasInputKeyJustPressed(EKeys::Down))
                        {
                            TitleWidgetInstance->ExitButtonHovered();
                            TitleWidgetInstance->StartButtonUnHovered();
                        }
                    }
                    break;
                    case ETitleMenuType::Setting:
                    {
                        TEXT("Missing Type");
                        return;
                    }
                    break;
                    case ETitleMenuType::Exit:
                    {
                        if (HUDPlayerController->WasInputKeyJustPressed(EKeys::Enter))
                        {
                            TitleWidgetInstance->ExitButtonClicked();
                        }
                        else if (HUDPlayerController->WasInputKeyJustPressed(EKeys::Up) ||
                            HUDPlayerController->WasInputKeyJustPressed(EKeys::Down))
                        {
                            TitleWidgetInstance->StartButtonHovered();
                            TitleWidgetInstance->ExitButtonUnHovered();
                        }
                    }
                    break;
                    case ETitleMenuType::None:
                    {
                        if (HUDPlayerController->WasInputKeyJustPressed(EKeys::Up) ||
                            HUDPlayerController->WasInputKeyJustPressed(EKeys::Down))
                        {
                            TitleWidgetInstance->StartButtonHovered();
                        }

                        TitleWidgetInstance->SetUnHovered();
                    }
                    break;
                    }
                }
            }
        },
        .End = [this]() // End
        {
            TitleWidgetInstance->SetVisibility(ESlateVisibility::Hidden);
            bIsAnykeyHandled = false;
            TitleWidgetInstance->SetUnHovered();
            TitleWidgetInstance->SetIsEnd(false);
        }
        }
    );

    // Title
    TitleFSM->CreateState({
        .StateValue = static_cast<int64>(ETitleFSMState::CHARACTERSELECT),
        .Start = [this]()  // Start
        {
            CharacterWidgetInstance->SetVisibility(ESlateVisibility::Visible);
            CharacterWidgetInstance->PlayFadeAnimation();
        },
        .Update = [this](float DeltaTime)  // Update
        {
            if (true == CharacterWidgetInstance->GetIsEnd())
            {
                TitleFSM->ChangeState(static_cast<int64>(ETitleFSMState::MENU));
            }

            if (true == CharacterWidgetInstance->IsButtonHovered())
            {
                return;
            }
            else
            {
                ECharacterType TypeValue = CharacterWidgetInstance->GetCharacterType();
                switch (TypeValue)
                {
                case ECharacterType::Nero:
                {
                    if (HUDPlayerController->WasInputKeyJustPressed(EKeys::Enter))
                    {
                        CharacterWidgetInstance->NeroButtonClicked();
                    }
                    else if (HUDPlayerController->WasInputKeyJustPressed(EKeys::Left) ||
                        HUDPlayerController->WasInputKeyJustPressed(EKeys::Right))
                    {
                        CharacterWidgetInstance->VergilButtonHovered();
                        CharacterWidgetInstance->NeroButtonUnHovered();
                    }
                }
                break;
                case ECharacterType::Vergil:
                {
                    if (HUDPlayerController->WasInputKeyJustPressed(EKeys::Enter))
                    {
                        CharacterWidgetInstance->VergilButtonClicked();
                    }
                    else if (HUDPlayerController->WasInputKeyJustPressed(EKeys::Left) ||
                        HUDPlayerController->WasInputKeyJustPressed(EKeys::Right))
                    {
                        CharacterWidgetInstance->NeroButtonHovered();
                        CharacterWidgetInstance->VergilButtonUnHovered();
                    }
                }
                break;
                case ECharacterType::None:
                {
                    if (HUDPlayerController->WasInputKeyJustPressed(EKeys::Left))
                    {
                        CharacterWidgetInstance->NeroButtonHovered();
                    }
                    else if (HUDPlayerController->WasInputKeyJustPressed(EKeys::Right))
                    {
                        CharacterWidgetInstance->VergilButtonHovered();
                    }

                    CharacterWidgetInstance->SetUnHovered();
                }
                break;
                }
            }
        },
        .End = [this]() // End
        {
            CharacterWidgetInstance->SetVisibility(ESlateVisibility::Hidden);
            CharacterWidgetInstance->SetIsEnd(false);
            CharacterWidgetInstance->SetUnHovered();
        }
        }
    );

    // Menu
    TitleFSM->CreateState({
        .StateValue = static_cast<int64>(ETitleFSMState::MENU),
        .Start = [this]()  // Start
        {
            MenuWidgetInstance->SetVisibility(ESlateVisibility::Visible);
            MenuWidgetInstance->PlayFadeAnimation();
        },
        .Update = [this](float DeltaTime)  // Update
        {

        },
        .End = [this]() // End
        {
            MenuWidgetInstance->SetVisibility(ESlateVisibility::Hidden);
        }
        }
    );

    TitleFSM->ChangeState(static_cast<int64>(ETitleFSMState::LOGO));
}

void ATitleHUD::ClassSetting()
{
    static ConstructorHelpers::FClassFinder<UUserWidget> BGBlackWidgetClassFinder(TEXT("/Game/UI/Basic/WBP_BlackBGWidget"));
    if (BGBlackWidgetClassFinder.Succeeded())
    {
        BGBlackWidgetClass = BGBlackWidgetClassFinder.Class;
    }

    static ConstructorHelpers::FClassFinder<UUserWidget> TitleLogoWidgetClassFinder(TEXT("/Game/UI/Title/WBP_TitleLogoWidget"));
    if (TitleLogoWidgetClassFinder.Succeeded())
    {
        TitleLogoWidgetClass = TitleLogoWidgetClassFinder.Class;
    }

    static ConstructorHelpers::FClassFinder<UUserWidget> TitleWidgetClassFinder(TEXT("/Game/UI/Title/WBP_TitleWidget"));
    if (TitleWidgetClassFinder.Succeeded())
    {
        TitleWidgetClass = TitleWidgetClassFinder.Class;
    }

    static ConstructorHelpers::FClassFinder<UUserWidget> CharacterWidgetClassFinder(TEXT("/Game/UI/Select/WBP_SelectCharacterWidget"));
    if (CharacterWidgetClassFinder.Succeeded())
    {
        CharacterWidgetClass = CharacterWidgetClassFinder.Class;
    }

    static ConstructorHelpers::FClassFinder<UUserWidget> MenuWidgetClassFinder(TEXT("/Game/UI/Select/WBP_SelectMenuWidget"));
    if (MenuWidgetClassFinder.Succeeded())
    {
        MenuWidgetClass = MenuWidgetClassFinder.Class;
    }

    EKeys::GetAllKeys(AllKeys);
}

void ATitleHUD::VariableSetting()
{
    HUDPlayerController = GetOwningPlayerController();

    // 순서대로 Create해야 Widget이 위에 덮어 씌워짐
    BGBlackWidgetInstance = CreateWidget<UBlackBGWidget>(GetWorld(), BGBlackWidgetClass);
    BGBlackWidgetInstance->AddToViewport();

    MenuWidgetInstance = CreateWidget<USelectMenuWidget>(GetWorld(), MenuWidgetClass);
    MenuWidgetInstance->AddToViewport();
    MenuWidgetInstance->SetVisibility(ESlateVisibility::Hidden);

    CharacterWidgetInstance = CreateWidget<USelectCharacterWidget>(GetWorld(), CharacterWidgetClass);
    CharacterWidgetInstance->AddToViewport();
    CharacterWidgetInstance->SetVisibility(ESlateVisibility::Hidden);

    TitleWidgetInstance = CreateWidget<UTitleWidget>(GetWorld(), TitleWidgetClass);
    TitleWidgetInstance->AddToViewport();
    TitleWidgetInstance->SetVisibility(ESlateVisibility::Hidden);

    TitleLogoWidgetInstance = CreateWidget<UTitleLogoWidget>(GetWorld(), TitleLogoWidgetClass);
    TitleLogoWidgetInstance->AddToViewport();
    TitleLogoWidgetInstance->SetVisibility(ESlateVisibility::Hidden);

    if (HUDPlayerController)
    {
        HUDPlayerController->SetShowMouseCursor(true);

        FInputModeGameAndUI InputMode;
        InputMode.SetWidgetToFocus(TitleWidgetInstance->TakeWidget());
        InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
        HUDPlayerController->SetInputMode(InputMode);
        HUDPlayerController->SetShowMouseCursor(true);
    }
}