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

void ATitleHUD::BeginPlay()
{
    Super::BeginPlay();

    HUDPlayerController = GetOwningPlayerController();

    // ������� Create�ؾ� Widget�� ���� ���� ������
    BGBlackWidgetInstance = CreateWidget<UBlackBGWidget>(GetWorld(), BGBlackWidgetClass);
    if (BGBlackWidgetClass)
    {
        BGBlackWidgetInstance->AddToViewport();
    }
    
    MenuWidgetInstance = CreateWidget<USelectMenuWidget>(GetWorld(), MenuWidgetClass);
    CharacterWidgetInstance = CreateWidget<USelectCharacterWidget>(GetWorld(), CharacterWidgetClass);
    TitleWidgetInstance = CreateWidget<UTitleWidget>(GetWorld(), TitleWidgetClass);
    TitleLogoWidgetInstance = CreateWidget<UTitleLogoWidget>(GetWorld(), TitleLogoWidgetClass);

    if (HUDPlayerController)
    {
        HUDPlayerController->SetShowMouseCursor(true);

        FInputModeGameAndUI InputMode;
        InputMode.SetWidgetToFocus(TitleWidgetInstance->TakeWidget());
        InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
        HUDPlayerController->SetInputMode(InputMode);
        HUDPlayerController->SetShowMouseCursor(true);
    }

    TitleLogoWidgetInstance->AddToViewport();
    TitleLogoWidgetInstance->PlayAnim();
}

void ATitleHUD::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (false == bIsCharacterSelectHandle)
    {
        TitleStep();
    }
    else if (false == bIsMenuSelectHandle)
    {
        SelectStep();
    }
    else
    {

    }
}

// BG Animation ���ε���
void ATitleHUD::TitleDelayEvent()
{
    bIsTitleDelayEventHandled = true;
    TitleWidgetInstance->AddToViewport();
}

void ATitleHUD::TitleStep()
{
    // Logo Animation End
    if (false == bIsTitleLogoHandled && TitleLogoWidgetInstance->IsAnimationEnd())
    {
        bIsTitleLogoHandled = true;

        // 1�� �� Animation �ǽ�
        TitleLogoWidgetInstance->SetVisibility(ESlateVisibility::Hidden);
        GetWorldTimerManager().SetTimer(
            TitleLogoAnimEndHandle,
            this,
            &ATitleHUD::TitleDelayEvent,
            1.0f,
            false
        );
    }

    // Delay Event End
    if (true == bIsTitleDelayEventHandled)
    {
        // TitleMenuWidget ���� Animation
        bIsTitleDelayEventHandled = false;
        TitleWidgetInstance->PlayBlinkAnimation();
    }

    // Any Key �Է� �� Animation ���� �� TitleMenu ����
    if (false == bIsTitleMenuHandled && true == bIsTitleLogoHandled)
    {
        for (const FKey& Key : AllKeys)
        {
            if (HUDPlayerController->WasInputKeyJustPressed(Key))
            {
                bIsTitleMenuHandled = true;
                TitleWidgetInstance->StopBlinkAnimation();
                TitleWidgetInstance->SetVisibileButton();
                break;
            }
        }
    }

    // Title �޴� ���� â Ȱ��ȭ ����
    if (true == bIsTitleMenuHandled)
    {
        if (true == TitleWidgetInstance->IsButtonHovered()) // ���콺 ȣ���� �߿��� �۵� X
        {
            return;
        }
        else // ���콺 ��ȣ���� �߿� �۵�(Ű���� �Է�)
        {
            ETitleMenuType TypeValue = TitleWidgetInstance->GetMenuType();
            switch (TypeValue)
            {
            case ETitleMenuType::MainMenu:
            {
                if (HUDPlayerController->WasInputKeyJustPressed(EKeys::Enter))
                {
                    TitleWidgetInstance->StartButtonClicked();
                    TitleWidgetInstance->SetIsEnd();
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

    if (true == TitleWidgetInstance->GetIsEnd())
    {
        CharacterWidgetInstance->AddToViewport();
        CharacterWidgetInstance->PlayFadeAnimation();
        bIsCharacterSelectHandle = true;
    }
}

void ATitleHUD::SelectStep()
{
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
                CharacterWidgetInstance->SetIsEnd();
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
                CharacterWidgetInstance->SetIsEnd();
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

    if (true == CharacterWidgetInstance->GetIsEnd())
    {
        MenuWidgetInstance->AddToViewport();
        MenuWidgetInstance->PlayFadeAnimation();
        bIsMenuSelectHandle = true;
    }
}

void ATitleHUD::MenuStep()
{

}