// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectMenuWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/EditableText.h"
#include "DevilMayCry/Helper/SoundManager.h"

bool USelectMenuWidget::Initialize()
{
    Super::Initialize();
    VariableSetting();
    bIsExtraWindowsHandled = false;
    bIsChangeLocation2 = false;
    bIsChangeHost = false;
    bIsChangeClient = false;
    bIsChangePrev = false;

	return true;
}

void USelectMenuWidget::PlayFadeAnimation()
{
	PlayAnimation(FadeAnimation);
}

FString USelectMenuWidget::GetIPAddress() const
{
    FString InputIP = IPAddressTextBox->GetText().ToString().TrimStartAndEnd();

    // 포트가 포함되어 있지 않으면 자동으로 7777 추가
    if (!InputIP.Contains(TEXT(":")))
    {
        InputIP += TEXT(":7777");
    }

    return InputIP;
}

///////////////// Start Button Options ////////////////////
/////////////////////////////////////////////////////////////
void USelectMenuWidget::StartButtonClicked()
{
    if (true == bIsExtraWindowsHandled)
    {
        return;
    }

    // UGameplayStatics::OpenLevel(this, TEXT("Location2"));
    //UGameplayStatics::OpenLevel(this, FName(TEXT("/Game/Scene/Location2")));
    // GetWorld()->ServerTravel(TEXT("/Game/Scene/Location2?listen"), false);
    SetIsChangeLocation2(true);

    SM->PlaySFX(SM->GetStartSound());
}

void USelectMenuWidget::StartButtonHovered()
{
    if (true == bIsExtraWindowsHandled)
    {
        return;
    }

    bIsHovered = true;
    // TitleTextBox->SetText(FText::FromString(TEXT("Exit the game")));
    if (EMenuType::Start == MenuType)
    {
        return;
    }

    // Move SizeImage when hovering
    UCanvasPanelSlot* StartButtonSlot = Cast<UCanvasPanelSlot>(MenuStartButton->Slot);
    if (StartButtonSlot)
    {
        FVector2D ButtonPos = StartButtonSlot->GetPosition();
        // FVector2D ButtonSize = StartButtonSlot->GetSize();
        UCanvasPanelSlot* SizeSlot = Cast<UCanvasPanelSlot>(MenuSizeImage->Slot);
        if (SizeSlot)
        {
            SizeSlot->SetPosition(ButtonPos);
        }
    }

    UCanvasPanelSlot* MenuStartTextSlot = Cast<UCanvasPanelSlot>(MenuStartTextBox->Slot);
    if (MenuStartTextSlot)
    {
        MenuStartTextSlot->SetPosition(FVector2D(175.0f, -200.f));
    }
    UCanvasPanelSlot* MenuSettingTextSlot = Cast<UCanvasPanelSlot>(MenuSettingTextBox->Slot);
    if (MenuSettingTextSlot)
    {
        MenuSettingTextSlot->SetPosition(FVector2D(160.0f, -120.f));
    }
    UCanvasPanelSlot* MenuPrevTextSlot = Cast<UCanvasPanelSlot>(MenuPrevTextBox->Slot);
    if (MenuPrevTextSlot)
    {
        MenuPrevTextSlot->SetPosition(FVector2D(160.0f, -40.f));
    }

    MenuType = EMenuType::Start;
    MenuStartTextBox->SetColorAndOpacity(FSlateColor(FLinearColor(0.15f, 0.5f, 0.52f, 1.0f)));
    MenuSettingTextBox->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f)));
    MenuPrevTextBox->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f)));

    PlayAnimation(SizeUpAnimation);

    SM->PlaySFX(SM->GetButtonSound());
}

void USelectMenuWidget::StartButtonUnHovered()
{
    SetUnHovered();

    if (true == bIsExtraWindowsHandled)
    {
        return;
    }
}

///////////////// Setting Button Options ////////////////////
/////////////////////////////////////////////////////////////

void USelectMenuWidget::SettingButtonClicked()
{
    if (true == bIsExtraWindowsHandled)
    {
        return;
    }

    bIsExtraWindowsHandled = true;
    MessageBox00Visible();
    PlayAnimation(MultiplayAnimation);

    SM->PlaySFX(SM->GetWindowSound());
}

void USelectMenuWidget::SettingButtonHovered()
{
    if (true == bIsExtraWindowsHandled)
    {
        return;
    }

    bIsHovered = true;
    // TitleTextBox->SetText(FText::FromString(TEXT("Exit the game")));
    if (EMenuType::Setting == MenuType)
    {
        return;
    }

    // Move SizeImage when hovering
    UCanvasPanelSlot* SettingButtonSlot = Cast<UCanvasPanelSlot>(MenuSettingButton->Slot);
    if (SettingButtonSlot)
    {
        FVector2D ButtonPos = SettingButtonSlot->GetPosition();
        // FVector2D ButtonSize = SettingButtonSlot->GetSize();
        UCanvasPanelSlot* SizeSlot = Cast<UCanvasPanelSlot>(MenuSizeImage->Slot);
        if (SizeSlot)
        {
            SizeSlot->SetPosition(ButtonPos);
        }
    }

    UCanvasPanelSlot* MenuSettingTextSlot = Cast<UCanvasPanelSlot>(MenuSettingTextBox->Slot);
    if (MenuSettingTextSlot)
    {
        MenuSettingTextSlot->SetPosition(FVector2D(175.0f, -120.f));
    }
    UCanvasPanelSlot* MenuStartTextSlot = Cast<UCanvasPanelSlot>(MenuStartTextBox->Slot);
    if (MenuStartTextSlot)
    {
        MenuStartTextSlot->SetPosition(FVector2D(160.0f, -200.f));
    }
    UCanvasPanelSlot* MenuPrevTextSlot = Cast<UCanvasPanelSlot>(MenuPrevTextBox->Slot);
    if (MenuPrevTextSlot)
    {
        MenuPrevTextSlot->SetPosition(FVector2D(160.0f, -40.f));
    }

    MenuType = EMenuType::Setting;
    MenuSettingTextBox->SetColorAndOpacity(FSlateColor(FLinearColor(0.15f, 0.5f, 0.52f, 1.0f)));
    MenuPrevTextBox->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f)));
    MenuStartTextBox->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f)));

    PlayAnimation(SizeUpAnimation);

    SM->PlaySFX(SM->GetButtonSound());
}

void USelectMenuWidget::SettingButtonUnHovered()
{
    SetUnHovered();

    if (true == bIsExtraWindowsHandled)
    {
        return;
    }
}

///////////////// Prev Button Options ////////////////////
/////////////////////////////////////////////////////////////

void USelectMenuWidget::PrevButtonClicked()
{
    if (true == bIsExtraWindowsHandled)
    {
        return;
    }

    bIsHovered = false;
    MenuType = EMenuType::None;

    UCanvasPanelSlot* MenuStartTextSlot = Cast<UCanvasPanelSlot>(MenuStartTextBox->Slot);
    if (MenuStartTextSlot)
    {
        MenuStartTextSlot->SetPosition(FVector2D(160.0f, -200.f));
    }
    UCanvasPanelSlot* MenuSettingTextSlot = Cast<UCanvasPanelSlot>(MenuSettingTextBox->Slot);
    if (MenuSettingTextSlot)
    {
        MenuSettingTextSlot->SetPosition(FVector2D(160.0f, -120.f));
    }
    UCanvasPanelSlot* MenuPrevTextSlot = Cast<UCanvasPanelSlot>(MenuPrevTextBox->Slot);
    if (MenuPrevTextSlot)
    {
        MenuPrevTextSlot->SetPosition(FVector2D(160.0f, -40.f));
    }
    UCanvasPanelSlot* SizeImageSlot = Cast<UCanvasPanelSlot>(MenuSizeImage->Slot);
    if (SizeImageSlot)
    {
        SizeImageSlot->SetPosition(FVector2D(0.f, -700.f));
    }

    MenuSettingTextBox->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f)));
    MenuPrevTextBox->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f)));
    MenuStartTextBox->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f)));

    SetIsChangePrev();

    SM->PlaySFX(SM->GetSelectSound());
}

void USelectMenuWidget::PrevButtonHovered()
{
    if (true == bIsExtraWindowsHandled)
    {
        return;
    }

    bIsHovered = true;
    // TitleTextBox->SetText(FText::FromString(TEXT("Exit the game")));
    if (EMenuType::Prev == MenuType)
    {
        return;
    }

    // Move SizeImage when hovering
    UCanvasPanelSlot* PrevButtonSlot = Cast<UCanvasPanelSlot>(MenuPrevButton->Slot);
    if (PrevButtonSlot)
    {
        FVector2D ButtonPos = PrevButtonSlot->GetPosition();
        // FVector2D ButtonSize = PrevButtonSlot->GetSize();
        UCanvasPanelSlot* SizeSlot = Cast<UCanvasPanelSlot>(MenuSizeImage->Slot);
        if (SizeSlot)
        {
            SizeSlot->SetPosition(ButtonPos);
        }
    }

    UCanvasPanelSlot* MenuPrevTextSlot = Cast<UCanvasPanelSlot>(MenuPrevTextBox->Slot);
    if (MenuPrevTextSlot)
    {
        MenuPrevTextSlot->SetPosition(FVector2D(175.0f, -40.f));
    }
    UCanvasPanelSlot* MenuSettingTextSlot = Cast<UCanvasPanelSlot>(MenuSettingTextBox->Slot);
    if (MenuSettingTextSlot)
    {
        MenuSettingTextSlot->SetPosition(FVector2D(160.0f, -120.f));
    }
    UCanvasPanelSlot* MenuStartTextSlot = Cast<UCanvasPanelSlot>(MenuStartTextBox->Slot);
    if (MenuStartTextSlot)
    {
        MenuStartTextSlot->SetPosition(FVector2D(160.0f, -200.f));
    }

    MenuType = EMenuType::Prev;
    MenuPrevTextBox->SetColorAndOpacity(FSlateColor(FLinearColor(0.15f, 0.5f, 0.52f, 1.0f)));
    MenuStartTextBox->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f)));
    MenuSettingTextBox->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f)));

    PlayAnimation(SizeUpAnimation);

    SM->PlaySFX(SM->GetButtonSound());
}

void USelectMenuWidget::PrevButtonUnHovered()
{
    SetUnHovered();

    if (true == bIsExtraWindowsHandled)
    {
        return;
    }
}

///////////////// Server Button Options ////////////////////
/////////////////////////////////////////////////////////////

void USelectMenuWidget::CreateButtonClicked()
{
    MessageBox00Hidden();
    MessageBox01Visible();
    MenuType = EMenuType::Message;
    MessageTextBox->SetText(FText::FromString(TEXT("Would you like to create a room?")));

    UCanvasPanelSlot* MenuSettingTextSlot = Cast<UCanvasPanelSlot>(MenuSettingTextBox->Slot);
    if (MenuSettingTextSlot)
    {
        MenuSettingTextSlot->SetPosition(FVector2D(160.0f, -120.f));
    }
    UCanvasPanelSlot* SizeImageSlot = Cast<UCanvasPanelSlot>(MenuSizeImage->Slot);
    if (SizeImageSlot)
    {
        SizeImageSlot->SetPosition(FVector2D(0.f, -700.f));
    }

    MenuSettingTextBox->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f)));
    MultiPlayTextBox00->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f)));
    MultiPlayTextBox01->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f)));

    PlayAnimation(MessageAnimation00);

    SM->PlaySFX(SM->GetSelectSound());
}

void USelectMenuWidget::CreateButtonHovered()
{
    bIsHovered = true;
    if (EMenuType::Create == MenuType)
    {
        return;
    }

    MultiPlayTextBox00->SetColorAndOpacity(FSlateColor(FLinearColor(0.15f, 0.5f, 0.52f, 1.0f)));
    MultiPlayTextBox01->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f)));

    MenuType = EMenuType::Create;

    SM->PlaySFX(SM->GetButtonSound2());
}

void USelectMenuWidget::CreateButtonUnHovered()
{
    SetUnHovered();
    // MultiPlayTextBox00->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f)));
    // MultiPlayTextBox01->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f)));
}

void USelectMenuWidget::JoinButtonClicked()
{
    MessageBox00Hidden();
    MessageBox02Visible();
    MenuType = EMenuType::Message;
    MessageTextBox->SetText(FText::FromString(TEXT("Enter the IP to connect to")));

    UCanvasPanelSlot* MenuSettingTextSlot = Cast<UCanvasPanelSlot>(MenuSettingTextBox->Slot);
    if (MenuSettingTextSlot)
    {
        MenuSettingTextSlot->SetPosition(FVector2D(160.0f, -120.f));
    }
    UCanvasPanelSlot* SizeImageSlot = Cast<UCanvasPanelSlot>(MenuSizeImage->Slot);
    if (SizeImageSlot)
    {
        SizeImageSlot->SetPosition(FVector2D(0.f, -700.f));
    }

    MenuSettingTextBox->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f)));
    MultiPlayTextBox00->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f)));
    MultiPlayTextBox01->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f)));

    PlayAnimation(MessageAnimation01);

    SM->PlaySFX(SM->GetSelectSound());
}

void USelectMenuWidget::JoinButtonHovered()
{
    bIsHovered = true;
    if (EMenuType::Join == MenuType)
    {
        return;
    }

    MultiPlayTextBox00->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f)));
    MultiPlayTextBox01->SetColorAndOpacity(FSlateColor(FLinearColor(0.15f, 0.5f, 0.52f, 1.0f)));

    MenuType = EMenuType::Join;

    SM->PlaySFX(SM->GetButtonSound2());
}

void USelectMenuWidget::JoinButtonUnHovered()
{
    SetUnHovered();
    // MultiPlayTextBox00->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f)));
    // MultiPlayTextBox01->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f)));
}

void USelectMenuWidget::ResetClicked()
{
    if (bIsExtraWindowsHandled)
    {
        bIsExtraWindowsHandled = false;
        MessageBox00Hidden();
        MenuType = EMenuType::None;
    }

    UCanvasPanelSlot* MenuSettingTextSlot = Cast<UCanvasPanelSlot>(MenuSettingTextBox->Slot);
    if (MenuSettingTextSlot)
    {
        MenuSettingTextSlot->SetPosition(FVector2D(160.0f, -120.f));
    }
    UCanvasPanelSlot* SizeImageSlot = Cast<UCanvasPanelSlot>(MenuSizeImage->Slot);
    if (SizeImageSlot)
    {
        SizeImageSlot->SetPosition(FVector2D(0.f, -700.f));
    }

    MenuSettingTextBox->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f)));
    MultiPlayTextBox00->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f)));
    MultiPlayTextBox01->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f)));

    SM->PlaySFX(SM->GetWindowSound());
}

void USelectMenuWidget::YesButtonClicked()
{
    bIsExtraWindowsHandled = false;
    bIsHovered = false;
    MenuType = EMenuType::None;
    MessageBox00Hidden();
    MessageBox01Hidden();

    UCanvasPanelSlot* MenuSettingTextSlot = Cast<UCanvasPanelSlot>(MenuSettingTextBox->Slot);
    if (MenuSettingTextSlot)
    {
        MenuSettingTextSlot->SetPosition(FVector2D(160.0f, -120.f));
    }
    UCanvasPanelSlot* SizeImageSlot = Cast<UCanvasPanelSlot>(MenuSizeImage->Slot);
    if (SizeImageSlot)
    {
        SizeImageSlot->SetPosition(FVector2D(0.f, -700.f));
    }

    MenuSettingTextBox->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f)));
    MultiPlayTextBox00->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f)));
    MultiPlayTextBox01->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f)));
    MessageCheckTextBox00->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f)));
    MessageCheckTextBox01->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f)));

    SetIsChangeHost();

    SM->PlaySFX(SM->GetSelectSound());
}

void USelectMenuWidget::YesButtonHovered()
{
    bIsHovered = true;
    if (EMenuType::YesCheck == MenuType)
    {
        return;
    }

    MessageCheckTextBox00->SetColorAndOpacity(FSlateColor(FLinearColor(0.15f, 0.5f, 0.52f, 1.0f)));
    MessageCheckTextBox01->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f)));
    MenuType = EMenuType::YesCheck;

    SM->PlaySFX(SM->GetButtonSound2());
}

void USelectMenuWidget::YesButtonUnHovered()
{
    SetUnHovered();
}

void USelectMenuWidget::NoButtonClicked()
{
    bIsExtraWindowsHandled = false;
    bIsHovered = false;
    MenuType = EMenuType::None;
    MessageBox00Hidden();
    MessageBox01Hidden();

    UCanvasPanelSlot* MenuSettingTextSlot = Cast<UCanvasPanelSlot>(MenuSettingTextBox->Slot);
    if (MenuSettingTextSlot)
    {
        MenuSettingTextSlot->SetPosition(FVector2D(160.0f, -120.f));
    }
    UCanvasPanelSlot* SizeImageSlot = Cast<UCanvasPanelSlot>(MenuSizeImage->Slot);
    if (SizeImageSlot)
    {
        SizeImageSlot->SetPosition(FVector2D(0.f, -700.f));
    }

    MenuSettingTextBox->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f)));
    MultiPlayTextBox00->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f)));
    MultiPlayTextBox01->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f)));
    MessageCheckTextBox00->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f)));
    MessageCheckTextBox01->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f)));

    SM->PlaySFX(SM->GetWindowSound());
}

void USelectMenuWidget::NoButtonHovered()
{
    bIsHovered = true;
    if (EMenuType::NoCheck == MenuType)
    {
        return;
    }

    MessageCheckTextBox00->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f)));
    MessageCheckTextBox01->SetColorAndOpacity(FSlateColor(FLinearColor(0.15f, 0.5f, 0.52f, 1.0f)));
    MenuType = EMenuType::NoCheck;

    SM->PlaySFX(SM->GetButtonSound2());
}

void USelectMenuWidget::NoButtonUnHovered()
{
    SetUnHovered();
}

void USelectMenuWidget::EnterButtonClicked()
{
    bIsExtraWindowsHandled = false;
    bIsHovered = false;
    MenuType = EMenuType::None;
    MessageBox00Hidden();
    MessageBox02Hidden();

    UCanvasPanelSlot* MenuSettingTextSlot = Cast<UCanvasPanelSlot>(MenuSettingTextBox->Slot);
    if (MenuSettingTextSlot)
    {
        MenuSettingTextSlot->SetPosition(FVector2D(160.0f, -120.f));
    }
    UCanvasPanelSlot* SizeImageSlot = Cast<UCanvasPanelSlot>(MenuSizeImage->Slot);
    if (SizeImageSlot)
    {
        SizeImageSlot->SetPosition(FVector2D(0.f, -700.f));
    }

    MenuSettingTextBox->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f)));
    MultiPlayTextBox00->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f)));
    MultiPlayTextBox01->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f)));
    MessageCheckTextBox02->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f)));
    MessageCheckTextBox03->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f)));

    SetIsChangeClient();

    SM->PlaySFX(SM->GetSelectSound());
}

void USelectMenuWidget::EnterButtonHovered()
{
    bIsHovered = true;
    if (EMenuType::EnterCheck == MenuType)
    {
        return;
    }

    MessageCheckTextBox02->SetColorAndOpacity(FSlateColor(FLinearColor(0.15f, 0.5f, 0.52f, 1.0f)));
    MessageCheckTextBox03->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f)));
    MenuType = EMenuType::EnterCheck;

    SM->PlaySFX(SM->GetButtonSound2());
}

void USelectMenuWidget::EnterButtonUnHovered()
{
    SetUnHovered();
}

void USelectMenuWidget::BackButtonClicked()
{
    bIsExtraWindowsHandled = false;
    bIsHovered = false;
    MenuType = EMenuType::None;
    MessageBox00Hidden();
    MessageBox02Hidden();

    UCanvasPanelSlot* MenuSettingTextSlot = Cast<UCanvasPanelSlot>(MenuSettingTextBox->Slot);
    if (MenuSettingTextSlot)
    {
        MenuSettingTextSlot->SetPosition(FVector2D(160.0f, -120.f));
    }
    UCanvasPanelSlot* SizeImageSlot = Cast<UCanvasPanelSlot>(MenuSizeImage->Slot);
    if (SizeImageSlot)
    {
        SizeImageSlot->SetPosition(FVector2D(0.f, -700.f));
    }

    MenuSettingTextBox->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f)));
    MultiPlayTextBox00->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f)));
    MultiPlayTextBox01->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f)));
    MessageCheckTextBox02->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f)));
    MessageCheckTextBox03->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f)));

    SM->PlaySFX(SM->GetWindowSound());
}

void USelectMenuWidget::BackButtonHovered()
{
    bIsHovered = true;
    if (EMenuType::BackCheck == MenuType)
    {
        return;
    }

    MessageCheckTextBox02->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f)));
    MessageCheckTextBox03->SetColorAndOpacity(FSlateColor(FLinearColor(0.15f, 0.5f, 0.52f, 1.0f)));
    MenuType = EMenuType::BackCheck;

    SM->PlaySFX(SM->GetButtonSound2());
}

void USelectMenuWidget::BackButtonUnHovered()
{
    SetUnHovered();
}

void USelectMenuWidget::MessageBox00Visible()
{
    MultiPlayImage->SetVisibility(ESlateVisibility::Visible);
    MultiPlayTextBox00->SetVisibility(ESlateVisibility::Visible);
    MultiPlayTextBox01->SetVisibility(ESlateVisibility::Visible);
    CreateRoomButton->SetVisibility(ESlateVisibility::Visible);
    JoinRoomButton->SetVisibility(ESlateVisibility::Visible);
    ResetStateButton->SetVisibility(ESlateVisibility::Visible);
}

void USelectMenuWidget::MessageBox00Hidden()
{
    MultiPlayImage->SetVisibility(ESlateVisibility::Hidden);
    MultiPlayTextBox00->SetVisibility(ESlateVisibility::Hidden);
    MultiPlayTextBox01->SetVisibility(ESlateVisibility::Hidden);
    CreateRoomButton->SetVisibility(ESlateVisibility::Hidden);
    JoinRoomButton->SetVisibility(ESlateVisibility::Hidden);
    ResetStateButton->SetVisibility(ESlateVisibility::Hidden);
}

void USelectMenuWidget::MessageBox01Visible()
{
    MessageImage->SetVisibility(ESlateVisibility::Visible);
    MessageTextBox->SetVisibility(ESlateVisibility::Visible);
    MessageCheckImage00->SetVisibility(ESlateVisibility::Visible);
    MessageCheckImage01->SetVisibility(ESlateVisibility::Visible);
    MessageCheckTextBox00->SetVisibility(ESlateVisibility::Visible);
    MessageCheckTextBox01->SetVisibility(ESlateVisibility::Visible);
    MessageCheckButton00->SetVisibility(ESlateVisibility::Visible);
    MessageCheckButton01->SetVisibility(ESlateVisibility::Visible);
}

void USelectMenuWidget::MessageBox01Hidden()
{
    MessageImage->SetVisibility(ESlateVisibility::Hidden);
    MessageTextBox->SetVisibility(ESlateVisibility::Hidden);
    MessageCheckImage00->SetVisibility(ESlateVisibility::Hidden);
    MessageCheckImage01->SetVisibility(ESlateVisibility::Hidden);
    MessageCheckTextBox00->SetVisibility(ESlateVisibility::Hidden);
    MessageCheckTextBox01->SetVisibility(ESlateVisibility::Hidden);
    MessageCheckButton00->SetVisibility(ESlateVisibility::Hidden);
    MessageCheckButton01->SetVisibility(ESlateVisibility::Hidden);
}

void USelectMenuWidget::MessageBox02Visible()
{
    MessageImage->SetVisibility(ESlateVisibility::Visible);
    MessageTextBox->SetVisibility(ESlateVisibility::Visible);
    IPAddressTextBox->SetVisibility(ESlateVisibility::Visible);
    IPAddressImage->SetVisibility(ESlateVisibility::Visible);
    MessageCheckImage02->SetVisibility(ESlateVisibility::Visible);
    MessageCheckImage03->SetVisibility(ESlateVisibility::Visible);
    MessageCheckTextBox02->SetVisibility(ESlateVisibility::Visible);
    MessageCheckTextBox03->SetVisibility(ESlateVisibility::Visible);
    MessageCheckButton02->SetVisibility(ESlateVisibility::Visible);
    MessageCheckButton03->SetVisibility(ESlateVisibility::Visible);
}

void USelectMenuWidget::MessageBox02Hidden()
{
    MessageImage->SetVisibility(ESlateVisibility::Hidden);
    MessageTextBox->SetVisibility(ESlateVisibility::Hidden);
    IPAddressTextBox->SetVisibility(ESlateVisibility::Hidden);
    IPAddressImage->SetVisibility(ESlateVisibility::Hidden);
    MessageCheckImage02->SetVisibility(ESlateVisibility::Hidden);
    MessageCheckImage03->SetVisibility(ESlateVisibility::Hidden);
    MessageCheckTextBox02->SetVisibility(ESlateVisibility::Hidden);
    MessageCheckTextBox03->SetVisibility(ESlateVisibility::Hidden);
    MessageCheckButton02->SetVisibility(ESlateVisibility::Hidden);
    MessageCheckButton03->SetVisibility(ESlateVisibility::Hidden);
}

///////////////// Setting function ////////////////////
///////////////////////////////////////////////////

void USelectMenuWidget::VariableSetting()
{
    if (MenuStartButton) // StartButton Setting
    {
        MenuStartButton->OnClicked.AddDynamic(this, &USelectMenuWidget::StartButtonClicked);
        MenuStartButton->OnHovered.AddDynamic(this, &USelectMenuWidget::StartButtonHovered);
        MenuStartButton->OnUnhovered.AddDynamic(this, &USelectMenuWidget::StartButtonUnHovered);

        UCanvasPanelSlot* StartButtonSlot = Cast<UCanvasPanelSlot>(MenuStartButton->Slot);
        if (StartButtonSlot)
        {
            StartButtonSlot->SetAnchors(FAnchors(0.0f, 0.5f));
            StartButtonSlot->SetAlignment(FVector2D(0.0f, 0.5f));
            StartButtonSlot->SetPosition(FVector2D(140.0f, -195.f));
            StartButtonSlot->SetSize(FVector2D(330.f, 40.f));
        }

        // MenuStartButton->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 0.0f));
    }

    if (MenuSettingButton) // StartButton Setting
    {
        MenuSettingButton->OnClicked.AddDynamic(this, &USelectMenuWidget::SettingButtonClicked);
        MenuSettingButton->OnHovered.AddDynamic(this, &USelectMenuWidget::SettingButtonHovered);
        MenuSettingButton->OnUnhovered.AddDynamic(this, &USelectMenuWidget::SettingButtonUnHovered);

        UCanvasPanelSlot* SettingButtonSlot = Cast<UCanvasPanelSlot>(MenuSettingButton->Slot);
        if (SettingButtonSlot)
        {
            SettingButtonSlot->SetAnchors(FAnchors(0.0f, 0.5f));
            SettingButtonSlot->SetAlignment(FVector2D(0.0f, 0.5f));
            SettingButtonSlot->SetPosition(FVector2D(140.0f, -115.f));
            SettingButtonSlot->SetSize(FVector2D(330.f, 40.f));
        }

        // MenuSettingButton->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 0.0f));
    }

    if (MenuPrevButton) // StartButton Setting
    {
        MenuPrevButton->OnClicked.AddDynamic(this, &USelectMenuWidget::PrevButtonClicked);
        MenuPrevButton->OnHovered.AddDynamic(this, &USelectMenuWidget::PrevButtonHovered);
        MenuPrevButton->OnUnhovered.AddDynamic(this, &USelectMenuWidget::PrevButtonUnHovered);

        UCanvasPanelSlot* PrevButtonSlot = Cast<UCanvasPanelSlot>(MenuPrevButton->Slot);
        if (PrevButtonSlot)
        {
            PrevButtonSlot->SetAnchors(FAnchors(0.0f, 0.5f));
            PrevButtonSlot->SetAlignment(FVector2D(0.0f, 0.5f));
            PrevButtonSlot->SetPosition(FVector2D(140.0f, -35.f));
            PrevButtonSlot->SetSize(FVector2D(330.f, 40.f));
        }

        // MenuSettingButton->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 0.0f));
    }

    UCanvasPanelSlot* SizeImageSlot = Cast<UCanvasPanelSlot>(MenuSizeImage->Slot);
    if (SizeImageSlot)
    {
        SizeImageSlot->SetAnchors(FAnchors(0.0f, 0.5f));
        SizeImageSlot->SetAlignment(FVector2D(0.0f, 0.5f));
        SizeImageSlot->SetPosition(FVector2D(0.f, -700.f));
        SizeImageSlot->SetSize(FVector2D(300.f, 70.f));
    }

    UCanvasPanelSlot* MenuStartTextSlot = Cast<UCanvasPanelSlot>(MenuStartTextBox->Slot);
    if (MenuStartTextSlot)
    {
        MenuStartTextSlot->SetAnchors(FAnchors(0.0f, 0.5f));
        MenuStartTextSlot->SetAlignment(FVector2D(0.0f, 0.5f));
        MenuStartTextSlot->SetPosition(FVector2D(160.0f, -200.f));
        MenuStartTextSlot->SetSize(FVector2D(400.f, 60.f));

        FSlateFontInfo FontInfo;
        FontInfo.FontObject = LoadObject<UObject>(nullptr, TEXT("/Game/Asset/Font/DMC5Font_Font"));
        FontInfo.TypefaceFontName = FName("Default");
        FontInfo.Size = 40;
        FontInfo.LetterSpacing = 100;

        MenuStartTextBox->SetFont(FontInfo);
        MenuStartTextBox->SetJustification(ETextJustify::Left);
        MenuStartTextBox->SetText(FText::FromString(TEXT("Mission Start")));
        MenuStartTextBox->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f)));
    }

    UCanvasPanelSlot* MenuSettingTextSlot = Cast<UCanvasPanelSlot>(MenuSettingTextBox->Slot);
    if (MenuSettingTextSlot)
    {
        MenuSettingTextSlot->SetAnchors(FAnchors(0.0f, 0.5f));
        MenuSettingTextSlot->SetAlignment(FVector2D(0.0f, 0.5f));
        MenuSettingTextSlot->SetPosition(FVector2D(160.0f, -120.f));
        MenuSettingTextSlot->SetSize(FVector2D(400.f, 60.f));

        FSlateFontInfo FontInfo;
        FontInfo.FontObject = LoadObject<UObject>(nullptr, TEXT("/Game/Asset/Font/DMC5Font_Font"));
        FontInfo.TypefaceFontName = FName("Default");
        FontInfo.Size = 40;
        FontInfo.LetterSpacing = 100;

        MenuSettingTextBox->SetFont(FontInfo);
        MenuSettingTextBox->SetJustification(ETextJustify::Left);
        MenuSettingTextBox->SetText(FText::FromString(TEXT("Multiplay")));
        MenuSettingTextBox->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f)));
    }

    UCanvasPanelSlot* MenuPrevTextSlot = Cast<UCanvasPanelSlot>(MenuPrevTextBox->Slot);
    if (MenuPrevTextSlot)
    {
        MenuPrevTextSlot->SetAnchors(FAnchors(0.0f, 0.5f));
        MenuPrevTextSlot->SetAlignment(FVector2D(0.0f, 0.5f));
        MenuPrevTextSlot->SetPosition(FVector2D(160.0f, -40.f));
        MenuPrevTextSlot->SetSize(FVector2D(400.f, 60.f));

        FSlateFontInfo FontInfo;
        FontInfo.FontObject = LoadObject<UObject>(nullptr, TEXT("/Game/Asset/Font/DMC5Font_Font"));
        FontInfo.TypefaceFontName = FName("Default");
        FontInfo.Size = 40;
        FontInfo.LetterSpacing = 100;

        MenuPrevTextBox->SetFont(FontInfo);
        MenuPrevTextBox->SetJustification(ETextJustify::Left);
        MenuPrevTextBox->SetText(FText::FromString(TEXT("Character Select")));
        MenuPrevTextBox->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f)));
    }

    UCanvasPanelSlot* MenuMissionSlot = Cast<UCanvasPanelSlot>(MenuMissionImage->Slot);
    if (MenuMissionSlot)
    {
        MenuMissionSlot->SetAnchors(FAnchors(0.0f, 0.5f));
        MenuMissionSlot->SetAlignment(FVector2D(0.0f, 0.5f));
        MenuMissionSlot->SetPosition(FVector2D(136.0f, -360.0));
        MenuMissionSlot->SetSize(FVector2D(580.0f, 170.0f));
    }

    UCanvasPanelSlot* MenuBarImageSlot00 = Cast<UCanvasPanelSlot>(MenuBarImage00->Slot);
    if (MenuBarImageSlot00)
    {
        MenuBarImageSlot00->SetAnchors(FAnchors(1.0f, 0.5f));
        MenuBarImageSlot00->SetAlignment(FVector2D(1.0f, 0.5f));
        MenuBarImageSlot00->SetPosition(FVector2D(-6.0f, -100.0f));
        MenuBarImageSlot00->SetSize(FVector2D(765.0f, 4.0f));
    }

    UCanvasPanelSlot* MenuBarImageSlot01 = Cast<UCanvasPanelSlot>(MenuBarImage01->Slot);
    if (MenuBarImageSlot01)
    {
        MenuBarImageSlot01->SetAnchors(FAnchors(1.0f, 0.5f));
        MenuBarImageSlot01->SetAlignment(FVector2D(1.0f, 0.5f));
        MenuBarImageSlot01->SetPosition(FVector2D(-6.0f, 150.0));
        MenuBarImageSlot01->SetSize(FVector2D(765.0f, 4.0f));
    }

    UCanvasPanelSlot* MenuBarTextBoxSlot00 = Cast<UCanvasPanelSlot>(MenuBarTextBox00->Slot);
    if (MenuBarTextBoxSlot00)
    {
        MenuBarTextBoxSlot00->SetAnchors(FAnchors(1.0f, 0.5f));
        MenuBarTextBoxSlot00->SetAlignment(FVector2D(1.0f, 0.5f));
        MenuBarTextBoxSlot00->SetPosition(FVector2D(-595.0f, -128.0f));
        MenuBarTextBoxSlot00->SetSize(FVector2D(165.0f, 40.f));

        //FSlateFontInfo FontInfo;
        //FontInfo.FontObject = LoadObject<UObject>(nullptr, TEXT("/Game/Asset/Font/DMC5Font_Font"));
        //FontInfo.TypefaceFontName = FName("Default");
        //FontInfo.Size = 38;
        //FontInfo.LetterSpacing = 0;

        // MenuBarTextBox00->SetFont(FontInfo);
        MenuBarTextBox00->SetJustification(ETextJustify::Left);
        MenuBarTextBox00->SetText(FText::FromString(TEXT("PLAYER")));
        MenuBarTextBox00->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f)));
    }

    UCanvasPanelSlot* MenuBarTextBoxSlot01 = Cast<UCanvasPanelSlot>(MenuBarTextBox01->Slot);
    if (MenuBarTextBoxSlot01)
    {
        MenuBarTextBoxSlot01->SetAnchors(FAnchors(1.0f, 0.5f));
        MenuBarTextBoxSlot01->SetAlignment(FVector2D(1.0f, 0.5f));
        MenuBarTextBoxSlot01->SetPosition(FVector2D(-595.0f, 120.f));
        MenuBarTextBoxSlot01->SetSize(FVector2D(165.0f, 40.f));

        //FSlateFontInfo FontInfo;
        //FontInfo.FontObject = LoadObject<UObject>(nullptr, TEXT("/Game/Asset/Font/DMC5Font_Font"));
        //FontInfo.TypefaceFontName = FName("Default");
        //FontInfo.Size = 38;
        //FontInfo.LetterSpacing = 0;

        // MenuBarTextBox00->SetFont(FontInfo);
        MenuBarTextBox01->SetJustification(ETextJustify::Left);
        MenuBarTextBox01->SetText(FText::FromString(TEXT("INFORMATION")));
        MenuBarTextBox01->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f)));
    }

    //////////////////////server

    UCanvasPanelSlot* MultiPlayImageSlot = Cast<UCanvasPanelSlot>(MultiPlayImage->Slot);
    if (MenuMissionSlot)
    {
        MultiPlayImageSlot->SetAnchors(FAnchors(0.0f, 0.5f));
        MultiPlayImageSlot->SetAlignment(FVector2D(0.0f, 0.5f));
        MultiPlayImageSlot->SetPosition(FVector2D(550.0f, -73.f));
        MultiPlayImageSlot->SetSize(FVector2D(370.0f, 195.0f));
    }

    UCanvasPanelSlot* MultiPlayTextBoxSlot00 = Cast<UCanvasPanelSlot>(MultiPlayTextBox00->Slot);
    if (MenuStartTextSlot)
    {
        MultiPlayTextBoxSlot00->SetAnchors(FAnchors(0.0f, 0.5f));
        MultiPlayTextBoxSlot00->SetAlignment(FVector2D(0.0f, 0.5f));
        MultiPlayTextBoxSlot00->SetPosition(FVector2D(588.0f, -120.0f));
        MultiPlayTextBoxSlot00->SetSize(FVector2D(280.0f, 60.f));

        //FSlateFontInfo FontInfo;
        //FontInfo.FontObject = LoadObject<UObject>(nullptr, TEXT("/Game/Asset/Font/DMC5Font_Font"));
        //FontInfo.TypefaceFontName = FName("Default");
        //FontInfo.Size = 53.33f;
        //FontInfo.LetterSpacing = 100;

        // MultiPlayTextBox00->SetFont(FontInfo);
        MultiPlayTextBox00->SetJustification(ETextJustify::Left);
        MultiPlayTextBox00->SetText(FText::FromString(TEXT("Create Room")));
        MultiPlayTextBox00->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f)));
    }

    UCanvasPanelSlot* ResetStateButtonSlot = Cast<UCanvasPanelSlot>(ResetStateButton->Slot);
    if (MenuStartTextSlot)
    {
        ResetStateButtonSlot->SetAnchors(FAnchors(0.0f, 0.0f, 1.0f, 1.0f));
        ResetStateButtonSlot->SetAlignment(FVector2D(0.0f, 0.0f));
        ResetStateButtonSlot->SetPosition(FVector2D(0.0f, 0.0f));
        ResetStateButtonSlot->SetSize(FVector2D(0.0f, 0.0f));

        ResetStateButton->OnClicked.AddDynamic(this, &USelectMenuWidget::ResetClicked);
    }

    UCanvasPanelSlot* MultiPlayTextBoxSlot01 = Cast<UCanvasPanelSlot>(MultiPlayTextBox01->Slot);
    if (MenuStartTextSlot)
    {
        MultiPlayTextBoxSlot01->SetAnchors(FAnchors(0.0f, 0.5f));
        MultiPlayTextBoxSlot01->SetAlignment(FVector2D(0.0f, 0.5f));
        MultiPlayTextBoxSlot01->SetPosition(FVector2D(588.0f, -40.0f));
        MultiPlayTextBoxSlot01->SetSize(FVector2D(280.0f, 60.f));

        //FSlateFontInfo FontInfo;
        //FontInfo.FontObject = LoadObject<UObject>(nullptr, TEXT("/Game/Asset/Font/DMC5Font_Font"));
        //FontInfo.TypefaceFontName = FName("Default");
        //FontInfo.Size = 53.33f;
        //FontInfo.LetterSpacing = 100;

        // MultiPlayTextBox00->SetFont(FontInfo);
        MultiPlayTextBox01->SetJustification(ETextJustify::Left);
        MultiPlayTextBox01->SetText(FText::FromString(TEXT("Join Room")));
        MultiPlayTextBox01->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f)));
    }

    UCanvasPanelSlot* CreateRoomButtonSlot = Cast<UCanvasPanelSlot>(CreateRoomButton->Slot);
    if (CreateRoomButtonSlot)
    {
        CreateRoomButtonSlot->SetAnchors(FAnchors(0.0f, 0.5f));
        CreateRoomButtonSlot->SetAlignment(FVector2D(0.0f, 0.5f));
        CreateRoomButtonSlot->SetPosition(FVector2D(585.0f, -115.f));
        CreateRoomButtonSlot->SetSize(FVector2D(280.0f, 40.0f));

        CreateRoomButton->OnClicked.AddDynamic(this, &USelectMenuWidget::CreateButtonClicked);
        CreateRoomButton->OnHovered.AddDynamic(this, &USelectMenuWidget::CreateButtonHovered);
        CreateRoomButton->OnUnhovered.AddDynamic(this, &USelectMenuWidget::CreateButtonUnHovered);
    }

    UCanvasPanelSlot* JoinRoomButtonSlot = Cast<UCanvasPanelSlot>(JoinRoomButton->Slot);
    if (JoinRoomButtonSlot)
    {
        JoinRoomButtonSlot->SetAnchors(FAnchors(0.0f, 0.5f));
        JoinRoomButtonSlot->SetAlignment(FVector2D(0.0f, 0.5f));
        JoinRoomButtonSlot->SetPosition(FVector2D(585.0f, -35.0f));
        JoinRoomButtonSlot->SetSize(FVector2D(280.0f, 40.0f));

        JoinRoomButton->OnClicked.AddDynamic(this, &USelectMenuWidget::JoinButtonClicked);
        JoinRoomButton->OnHovered.AddDynamic(this, &USelectMenuWidget::JoinButtonHovered);
        JoinRoomButton->OnUnhovered.AddDynamic(this, &USelectMenuWidget::JoinButtonUnHovered);
    }

    UCanvasPanelSlot* MessageImageSlot = Cast<UCanvasPanelSlot>(MessageImage->Slot);
    if (MessageImageSlot)
    {
        MessageImageSlot->SetAnchors(FAnchors(0.5f, 0.5f));
        MessageImageSlot->SetAlignment(FVector2D(0.5f, 0.5f));
        MessageImageSlot->SetPosition(FVector2D(0.0f, 0.0f));
        MessageImageSlot->SetSize(FVector2D(620.0f, 200.f));

        // JoinRoomButton->OnClicked.AddDynamic(this, &USelectMenuWidget::JoinButtonClicked);
        // JoinRoomButton->OnHovered.AddDynamic(this, &USelectMenuWidget::JoinButtonHovered);
        // JoinRoomButton->OnUnhovered.AddDynamic(this, &USelectMenuWidget::JoinButtonUnHovered);
    }

    UCanvasPanelSlot* MessageTextBoxSlot = Cast<UCanvasPanelSlot>(MessageTextBox->Slot);
    if (MessageTextBoxSlot)
    {
        MessageTextBoxSlot->SetAnchors(FAnchors(0.5f, 0.5f));
        MessageTextBoxSlot->SetAlignment(FVector2D(0.5f, 0.5f));
        MessageTextBoxSlot->SetPosition(FVector2D(0.f, -50.0f));
        MessageTextBoxSlot->SetSize(FVector2D(585.0f, 50.0f));

        //FSlateFontInfo FontInfo;
        //FontInfo.FontObject = LoadObject<UObject>(nullptr, TEXT("/Game/Asset/Font/DMC5Font_Font"));
        //FontInfo.TypefaceFontName = FName("Default");
        //FontInfo.Size = 53.33f;
        //FontInfo.LetterSpacing = 100;

        // MultiPlayTextBox00->SetFont(FontInfo);
        MessageTextBox->SetJustification(ETextJustify::Center);
        MessageTextBox->SetText(FText::FromString(TEXT("Enter the IP to connect to")));
        MessageTextBox->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f)));
    }

    ///// [1]

    UCanvasPanelSlot* MessageCheckImageSlot00 = Cast<UCanvasPanelSlot>(MessageCheckImage00->Slot);
    if (MessageCheckImageSlot00)
    {
        MessageCheckImageSlot00->SetAnchors(FAnchors(0.5f, 0.5f));
        MessageCheckImageSlot00->SetAlignment(FVector2D(0.5f, 0.5f));
        MessageCheckImageSlot00->SetPosition(FVector2D(-140.f, 35.0f));
        MessageCheckImageSlot00->SetSize(FVector2D(200.0f, 60.0f));
    }

    UCanvasPanelSlot* MessageCheckImageSlot01 = Cast<UCanvasPanelSlot>(MessageCheckImage01->Slot);
    if (MessageCheckImageSlot01)
    {
        MessageCheckImageSlot01->SetAnchors(FAnchors(0.5f, 0.5f));
        MessageCheckImageSlot01->SetAlignment(FVector2D(0.5f, 0.5f));
        MessageCheckImageSlot01->SetPosition(FVector2D(140.f, 35.0f));
        MessageCheckImageSlot01->SetSize(FVector2D(200.0f, 60.0f));
    }

    UCanvasPanelSlot* MessageCheckTextBoxSlot00 = Cast<UCanvasPanelSlot>(MessageCheckTextBox00->Slot);
    if (MessageCheckTextBoxSlot00)
    {
        MessageCheckTextBoxSlot00->SetAnchors(FAnchors(0.5f, 0.5f));
        MessageCheckTextBoxSlot00->SetAlignment(FVector2D(0.5f, 0.5f));
        MessageCheckTextBoxSlot00->SetPosition(FVector2D(-140.f, 37.0f));
        MessageCheckTextBoxSlot00->SetSize(FVector2D(200.0f, 54.f));

        MessageCheckTextBox00->SetJustification(ETextJustify::Center);
        MessageCheckTextBox00->SetText(FText::FromString(TEXT("YES")));
        MessageCheckTextBox00->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f)));
    }

    UCanvasPanelSlot* MessageCheckTextBoxSlot01 = Cast<UCanvasPanelSlot>(MessageCheckTextBox01->Slot);
    if (MessageCheckTextBoxSlot01)
    {
        MessageCheckTextBoxSlot01->SetAnchors(FAnchors(0.5f, 0.5f));
        MessageCheckTextBoxSlot01->SetAlignment(FVector2D(0.5f, 0.5f));
        MessageCheckTextBoxSlot01->SetPosition(FVector2D(140.f, 37.0f));
        MessageCheckTextBoxSlot01->SetSize(FVector2D(200.0f, 54.f));

        MessageCheckTextBox01->SetJustification(ETextJustify::Center);
        MessageCheckTextBox01->SetText(FText::FromString(TEXT("NO")));
        MessageCheckTextBox01->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f)));
    }

    UCanvasPanelSlot* MessageCheckButtonSlot00 = Cast<UCanvasPanelSlot>(MessageCheckButton00->Slot);
    if (MessageCheckButtonSlot00)
    {
        MessageCheckButtonSlot00->SetAnchors(FAnchors(0.5f, 0.5f));
        MessageCheckButtonSlot00->SetAlignment(FVector2D(0.5f, 0.5f));
        MessageCheckButtonSlot00->SetPosition(FVector2D(-140.f, 35.0f));
        MessageCheckButtonSlot00->SetSize(FVector2D(200.0f, 60.0f));

        MessageCheckButton00->OnClicked.AddDynamic(this, &USelectMenuWidget::YesButtonClicked);
        MessageCheckButton00->OnHovered.AddDynamic(this, &USelectMenuWidget::YesButtonHovered);
        MessageCheckButton00->OnUnhovered.AddDynamic(this, &USelectMenuWidget::YesButtonUnHovered);
    }

    UCanvasPanelSlot* MessageCheckButtonSlot01 = Cast<UCanvasPanelSlot>(MessageCheckButton01->Slot);
    if (MessageCheckButtonSlot01)
    {
        MessageCheckButtonSlot01->SetAnchors(FAnchors(0.5f, 0.5f));
        MessageCheckButtonSlot01->SetAlignment(FVector2D(0.5f, 0.5f));
        MessageCheckButtonSlot01->SetPosition(FVector2D(140.f, 35.0f));
        MessageCheckButtonSlot01->SetSize(FVector2D(200.0f, 60.0f));

        MessageCheckButton01->OnClicked.AddDynamic(this, &USelectMenuWidget::NoButtonClicked);
        MessageCheckButton01->OnHovered.AddDynamic(this, &USelectMenuWidget::NoButtonHovered);
        MessageCheckButton01->OnUnhovered.AddDynamic(this, &USelectMenuWidget::NoButtonUnHovered);
    }

    ///// [2]

    UCanvasPanelSlot* MessageCheckImageSlot02 = Cast<UCanvasPanelSlot>(MessageCheckImage02->Slot);
    if (MessageCheckImageSlot02)
    {
        MessageCheckImageSlot02->SetAnchors(FAnchors(0.5f, 0.5f));
        MessageCheckImageSlot02->SetAlignment(FVector2D(0.5f, 0.5f));
        MessageCheckImageSlot02->SetPosition(FVector2D(110.0f, 35.0f));
        MessageCheckImageSlot02->SetSize(FVector2D(80.0f, 60.0f));
    }

    UCanvasPanelSlot* MessageCheckImageSlot03 = Cast<UCanvasPanelSlot>(MessageCheckImage03->Slot);
    if (MessageCheckImageSlot03)
    {
        MessageCheckImageSlot03->SetAnchors(FAnchors(0.5f, 0.5f));
        MessageCheckImageSlot03->SetAlignment(FVector2D(0.5f, 0.5f));
        MessageCheckImageSlot03->SetPosition(FVector2D(200.0f, 35.0f));
        MessageCheckImageSlot03->SetSize(FVector2D(80.0f, 60.0f));
    }

    UCanvasPanelSlot* MessageCheckTextBoxSlot02 = Cast<UCanvasPanelSlot>(MessageCheckTextBox02->Slot);
    if (MessageCheckTextBoxSlot02)
    {
        MessageCheckTextBoxSlot02->SetAnchors(FAnchors(0.5f, 0.5f));
        MessageCheckTextBoxSlot02->SetAlignment(FVector2D(0.5f, 0.5f));
        MessageCheckTextBoxSlot02->SetPosition(FVector2D(110.0f, 35.0f));
        MessageCheckTextBoxSlot02->SetSize(FVector2D(80.0f, 44.0f));

        MessageCheckTextBox02->SetJustification(ETextJustify::Center);
        MessageCheckTextBox02->SetText(FText::FromString(TEXT("Join")));
        MessageCheckTextBox02->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f)));
    }

    UCanvasPanelSlot* MessageCheckTextBoxSlot03 = Cast<UCanvasPanelSlot>(MessageCheckTextBox03->Slot);
    if (MessageCheckTextBoxSlot03)
    {
        MessageCheckTextBoxSlot03->SetAnchors(FAnchors(0.5f, 0.5f));
        MessageCheckTextBoxSlot03->SetAlignment(FVector2D(0.5f, 0.5f));
        MessageCheckTextBoxSlot03->SetPosition(FVector2D(200.0f, 35.0f));
        MessageCheckTextBoxSlot03->SetSize(FVector2D(80.0f, 44.0f));

        MessageCheckTextBox03->SetJustification(ETextJustify::Center);
        MessageCheckTextBox03->SetText(FText::FromString(TEXT("Back")));
        MessageCheckTextBox03->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f)));
    }

    UCanvasPanelSlot* MessageCheckButtonSlot02 = Cast<UCanvasPanelSlot>(MessageCheckButton02->Slot);
    if (MessageCheckButtonSlot02)
    {
        MessageCheckButtonSlot02->SetAnchors(FAnchors(0.5f, 0.5f));
        MessageCheckButtonSlot02->SetAlignment(FVector2D(0.5f, 0.5f));
        MessageCheckButtonSlot02->SetPosition(FVector2D(110.0f, 35.0f));
        MessageCheckButtonSlot02->SetSize(FVector2D(80.0f, 60.0f));

        MessageCheckButton02->OnClicked.AddDynamic(this, &USelectMenuWidget::EnterButtonClicked);
        MessageCheckButton02->OnHovered.AddDynamic(this, &USelectMenuWidget::EnterButtonHovered);
        MessageCheckButton02->OnUnhovered.AddDynamic(this, &USelectMenuWidget::EnterButtonUnHovered);
    }

    UCanvasPanelSlot* MessageCheckButtonSlot03 = Cast<UCanvasPanelSlot>(MessageCheckButton03->Slot);
    if (MessageCheckButtonSlot03)
    {
        MessageCheckButtonSlot03->SetAnchors(FAnchors(0.5f, 0.5f));
        MessageCheckButtonSlot03->SetAlignment(FVector2D(0.5f, 0.5f));
        MessageCheckButtonSlot03->SetPosition(FVector2D(200.0f, 35.0f));
        MessageCheckButtonSlot03->SetSize(FVector2D(80.0f, 60.0f));

        MessageCheckButton03->OnClicked.AddDynamic(this, &USelectMenuWidget::BackButtonClicked);
        MessageCheckButton03->OnHovered.AddDynamic(this, &USelectMenuWidget::BackButtonHovered);
        MessageCheckButton03->OnUnhovered.AddDynamic(this, &USelectMenuWidget::BackButtonUnHovered);
    }

    UCanvasPanelSlot* IPAddressTextBoxSlot = Cast<UCanvasPanelSlot>(IPAddressTextBox->Slot);
    if (IPAddressTextBoxSlot)
    {
        IPAddressTextBoxSlot->SetAnchors(FAnchors(0.5f, 0.5f));
        IPAddressTextBoxSlot->SetAlignment(FVector2D(0.5f, 0.5f));
        IPAddressTextBoxSlot->SetPosition(FVector2D(-84.0f, 38.f));
        IPAddressTextBoxSlot->SetSize(FVector2D(270.0f, 43.f));
    }

    UCanvasPanelSlot* IPAddressImageSlot = Cast<UCanvasPanelSlot>(IPAddressImage->Slot);
    if (IPAddressImageSlot)
    {
        IPAddressImageSlot->SetAnchors(FAnchors(0.5f, 0.5f));
        IPAddressImageSlot->SetAlignment(FVector2D(0.5f, 0.5f));
        IPAddressImageSlot->SetPosition(FVector2D(-85.0f, 35.f));
        IPAddressImageSlot->SetSize(FVector2D(283.f, 57.f));
    }

    MessageBox00Hidden();
    MessageBox01Hidden();
    MessageBox02Hidden();

    SM = GetGameInstance()->GetSubsystem<USoundManager>();
}
