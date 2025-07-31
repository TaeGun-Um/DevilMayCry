// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectMultiplayWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/CanvasPanelSlot.h"
#include "GameFramework/GameStateBase.h"
#include "DevilMayCry/State/LobbyPlayerState.h"
#include "DevilMayCry/System/LobbyGameModeBase.h"

bool USelectMultiplayWidget::Initialize()
{
	Super::Initialize();
	VariableSetting();
    bIsMessageHandled = false;
    bIsChangeLocation2 = false;
    bIsChangeSelectMenu = false;

	return true;
}

void USelectMultiplayWidget::NativeConstruct()
{
    Super::NativeConstruct();

    // 0.5초마다 플레이어 수 업데이트
    //GetWorld()->GetTimerManager().SetTimer(
    //    PlayerCountUpdateHandle, this, &USelectMultiplayWidget::UpdatePlayerCount, 0.5f, true);
        // Host 여부에 따라 Mission Start 버튼 제어

}

void USelectMultiplayWidget::StartButtonHidden()
{
    if (MenuStartButton)
    {
        MenuStartButton->SetVisibility(bIsHost ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
    }
}

void USelectMultiplayWidget::NativeDestruct()
{
    Super::NativeDestruct();

    // 타이머 제거
    //GetWorld()->GetTimerManager().ClearTimer(PlayerCountUpdateHandle);
}

void USelectMultiplayWidget::PlayFadeAnimation()
{
	PlayAnimation(FadeAnimation);
}

void USelectMultiplayWidget::SetLocalIP(FString _Text)
{
    LocalIP = _Text;
    FString FormattedText = FString::Printf(TEXT("Local IP : %s"), *LocalIP);
    MenuBarTextBox02->SetText(FText::FromString(FormattedText));
}

void USelectMultiplayWidget::SetPublicIP(FString _Text)
{
    PublicIP = _Text;
    FString FormattedText = FString::Printf(TEXT("Public IP : %s"), *PublicIP);
    MenuBarTextBox04->SetText(FText::FromString(FormattedText));
}

void USelectMultiplayWidget::UpdatePlayerCount()
{
    UWorld* World = GetWorld();
    if (!World) return;

    AGameStateBase* GameState = World->GetGameState();
    if (!GameState) return;

    int32 PlayerCount = GameState->PlayerArray.Num();

    FString PlayerText = FString::Printf(TEXT("Players : %d"), PlayerCount);
    MenuBarTextBox03->SetText(FText::FromString(PlayerText));
}

void USelectMultiplayWidget::UpdatePlayerSlot(int32 _PlayerIndex, bool _bIsConnected, bool _bIsReady)
{
    if (!PlayerSlots.IsValidIndex(_PlayerIndex) || !PlayerReadyTexts.IsValidIndex(_PlayerIndex))
    {
        return;
    }
    
    // 이미지 활성화/비활성
    PlayerSlots[_PlayerIndex]->SetVisibility(_bIsConnected ? ESlateVisibility::Visible : ESlateVisibility::Hidden);

    // Ready 상태 텍스트
    PlayerReadyTexts[_PlayerIndex]->SetText(_bIsReady ? FText::FromString(TEXT("Ready")) : FText::GetEmpty());
}

///////////////// Start Button Options
void USelectMultiplayWidget::StartButtonClicked()
{
    if (true == bIsMessageHandled)
    {
        return;
    }

    //if (false == bIsHost)
    //{
    //    return; // Host만 실행
    //}

    if (ALobbyGameModeBase* GM = GetWorld()->GetAuthGameMode<ALobbyGameModeBase>())
    {
        if (!GM->AllPlayersReady())
        {
            bIsMessageHandled = true;
            MessageTextBox->SetText(FText::FromString(TEXT("Not everyone is ready.")));
            MessageBox01Visible();
            PlayAnimation(MessageAnimation01);
            return;
        }

        UWorld* World = GetWorld();
        if (World)
        {
            World->ServerTravel("/Game/Scene/LoadingScene?listen");
        }
    }
}

void USelectMultiplayWidget::StartButtonHovered()
{
    if (true == bIsMessageHandled)
    {
        return;
    }

    bIsHovered = true;
    // TitleTextBox->SetText(FText::FromString(TEXT("Exit the game")));
    if (EMenuMultiPlayType::Start == MenuType)
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
    UCanvasPanelSlot* MenuSettingTextSlot = Cast<UCanvasPanelSlot>(MenuReadyTextBox->Slot);
    if (MenuSettingTextSlot)
    {
        MenuSettingTextSlot->SetPosition(FVector2D(160.0f, -120.f));
    }
    UCanvasPanelSlot* MenuPrevTextSlot = Cast<UCanvasPanelSlot>(MenuExitTextBox->Slot);
    if (MenuPrevTextSlot)
    {
        MenuPrevTextSlot->SetPosition(FVector2D(160.0f, -40.f));
    }

    MenuType = EMenuMultiPlayType::Start;
    MenuStartTextBox->SetColorAndOpacity(FSlateColor(FLinearColor(0.15f, 0.5f, 0.52f, 1.0f)));
    MenuReadyTextBox->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f)));
    MenuExitTextBox->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f)));

    PlayAnimation(SizeUpAnimation);
}

void USelectMultiplayWidget::StartButtonUnHovered()
{
    SetUnHovered();

    if (true == bIsMessageHandled)
    {
        return;
    }
}

///////////////// Ready Button Options
void USelectMultiplayWidget::ReadyButtonClicked()
{
    if (true == bIsMessageHandled)
    {
        return;
    }

    if (APlayerController* PC = GetOwningPlayer())
    {
        if (ALobbyPlayerState* PS = PC->GetPlayerState<ALobbyPlayerState>())
        {
            PS->ServerSetReady(true); // 서버에 RPC 호출
        }
    }
}

void USelectMultiplayWidget::ReadyButtonHovered()
{
    if (true == bIsMessageHandled)
    {
        return;
    }

    bIsHovered = true;
    // TitleTextBox->SetText(FText::FromString(TEXT("Exit the game")));
    if (EMenuMultiPlayType::Ready == MenuType)
    {
        return;
    }

    // Move SizeImage when hovering
    UCanvasPanelSlot* SettingButtonSlot = Cast<UCanvasPanelSlot>(MenuReadyButton->Slot);
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

    UCanvasPanelSlot* MenuSettingTextSlot = Cast<UCanvasPanelSlot>(MenuReadyTextBox->Slot);
    if (MenuSettingTextSlot)
    {
        MenuSettingTextSlot->SetPosition(FVector2D(175.0f, -120.f));
    }
    UCanvasPanelSlot* MenuStartTextSlot = Cast<UCanvasPanelSlot>(MenuStartTextBox->Slot);
    if (MenuStartTextSlot)
    {
        MenuStartTextSlot->SetPosition(FVector2D(160.0f, -200.f));
    }
    UCanvasPanelSlot* MenuPrevTextSlot = Cast<UCanvasPanelSlot>(MenuExitTextBox->Slot);
    if (MenuPrevTextSlot)
    {
        MenuPrevTextSlot->SetPosition(FVector2D(160.0f, -40.f));
    }

    MenuType = EMenuMultiPlayType::Ready;
    MenuReadyTextBox->SetColorAndOpacity(FSlateColor(FLinearColor(0.15f, 0.5f, 0.52f, 1.0f)));
    MenuExitTextBox->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f)));
    MenuStartTextBox->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f)));

    PlayAnimation(SizeUpAnimation);
}

void USelectMultiplayWidget::ReadyButtonUnHovered()
{
    SetUnHovered();

    if (true == bIsMessageHandled)
    {
        return;
    }
}

///////////////// Prev Button Options
void USelectMultiplayWidget::ExitButtonClicked()
{
    if (true == bIsMessageHandled)
    {
        return;
    }

    bIsMessageHandled = true;
    MessageTextBox->SetText(FText::FromString(TEXT("Are you sure leave the room?")));
    MessageBox00Visible();
    PlayAnimation(MessageAnimation00);
}

void USelectMultiplayWidget::ExitButtonHovered()
{
    if (true == bIsMessageHandled)
    {
        return;
    }

    bIsHovered = true;
    // TitleTextBox->SetText(FText::FromString(TEXT("Exit the game")));
    if (EMenuMultiPlayType::Exit == MenuType)
    {
        return;
    }

    // Move SizeImage when hovering
    UCanvasPanelSlot* PrevButtonSlot = Cast<UCanvasPanelSlot>(MenuExitTextBox->Slot);
    if (PrevButtonSlot)
    {
        FVector2D ButtonPos = PrevButtonSlot->GetPosition() + FVector2D(-15.f, 0.f);
        // FVector2D ButtonSize = PrevButtonSlot->GetSize();
        UCanvasPanelSlot* SizeSlot = Cast<UCanvasPanelSlot>(MenuSizeImage->Slot);
        if (SizeSlot)
        {
            SizeSlot->SetPosition(ButtonPos);
        }
    }

    UCanvasPanelSlot* MenuPrevTextSlot = Cast<UCanvasPanelSlot>(MenuExitTextBox->Slot);
    if (MenuPrevTextSlot)
    {
        MenuPrevTextSlot->SetPosition(FVector2D(175.0f, -40.f));
    }
    UCanvasPanelSlot* MenuSettingTextSlot = Cast<UCanvasPanelSlot>(MenuReadyTextBox->Slot);
    if (MenuSettingTextSlot)
    {
        MenuSettingTextSlot->SetPosition(FVector2D(160.0f, -120.f));
    }
    UCanvasPanelSlot* MenuStartTextSlot = Cast<UCanvasPanelSlot>(MenuStartTextBox->Slot);
    if (MenuStartTextSlot)
    {
        MenuStartTextSlot->SetPosition(FVector2D(160.0f, -200.f));
    }

    MenuType = EMenuMultiPlayType::Exit;
    MenuExitTextBox->SetColorAndOpacity(FSlateColor(FLinearColor(0.15f, 0.5f, 0.52f, 1.0f)));
    MenuStartTextBox->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f)));
    MenuReadyTextBox->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f)));

    PlayAnimation(SizeUpAnimation);
}

void USelectMultiplayWidget::ExitButtonUnHovered()
{
    SetUnHovered();

    if (true == bIsMessageHandled)
    {
        return;
    }
}

void USelectMultiplayWidget::YesButtonClicked()
{
    bIsMessageHandled = false;
    bIsHovered = false;
    MenuType = EMenuMultiPlayType::None;
    MessageBox00Hidden();

    UCanvasPanelSlot* MenuSettingTextSlot = Cast<UCanvasPanelSlot>(MenuExitTextBox->Slot);
    if (MenuSettingTextSlot)
    {
        MenuSettingTextSlot->SetPosition(FVector2D(160.0f, -40.f));
    }
    UCanvasPanelSlot* SizeImageSlot = Cast<UCanvasPanelSlot>(MenuSizeImage->Slot);
    if (SizeImageSlot)
    {
        SizeImageSlot->SetPosition(FVector2D(0.f, -700.f));
    }

    MenuExitTextBox->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f)));
    MessageCheckTextBox00->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f)));
    MessageCheckTextBox01->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f)));

    SetIsChangeMenu();
}

void USelectMultiplayWidget::YesButtonHovered()
{
    bIsHovered = true;
    if (EMenuMultiPlayType::YesCheck == MenuType)
    {
        return;
    }

    MessageCheckTextBox00->SetColorAndOpacity(FSlateColor(FLinearColor(0.15f, 0.5f, 0.52f, 1.0f)));
    MessageCheckTextBox01->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f)));
    MenuType = EMenuMultiPlayType::YesCheck;
}

void USelectMultiplayWidget::YesButtonUnHovered()
{
    SetUnHovered();
}

void USelectMultiplayWidget::NoButtonClicked()
{
    bIsMessageHandled = false;
    bIsHovered = false;
    MenuType = EMenuMultiPlayType::None;
    MessageBox00Hidden();

    UCanvasPanelSlot* MenuSettingTextSlot = Cast<UCanvasPanelSlot>(MenuExitTextBox->Slot);
    if (MenuSettingTextSlot)
    {
        MenuSettingTextSlot->SetPosition(FVector2D(160.0f, -40.f));
    }
    UCanvasPanelSlot* SizeImageSlot = Cast<UCanvasPanelSlot>(MenuSizeImage->Slot);
    if (SizeImageSlot)
    {
        SizeImageSlot->SetPosition(FVector2D(0.f, -700.f));
    }

    MenuExitTextBox->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f)));
    MessageCheckTextBox00->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f)));
    MessageCheckTextBox01->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f)));

    APlayerController* PC = GetOwningPlayer();
    if (PC == nullptr)
    {
        return;
    }

    UWorld* World = GetWorld();
    if (World == nullptr)
    {
        return;
    }

    // 클라이언트인 경우 서버와 연결 해제
    if (!PC->HasAuthority())
    {
        // 클라이언트는 서버 연결 해제 후 TitleScene으로 이동
        PC->ClientTravel("/Game/Maps/TitleScene", TRAVEL_Absolute);
    }
    else
    {
        // 서버는 전체를 TitleScene으로 보내야 하므로 ServerTravel
        World->ServerTravel("/Game/Maps/TitleScene?listen");
    }
}

void USelectMultiplayWidget::NoButtonHovered()
{
    bIsHovered = true;
    if (EMenuMultiPlayType::NoCheck == MenuType)
    {
        return;
    }

    MessageCheckTextBox00->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f)));
    MessageCheckTextBox01->SetColorAndOpacity(FSlateColor(FLinearColor(0.15f, 0.5f, 0.52f, 1.0f)));
    MenuType = EMenuMultiPlayType::NoCheck;
}

void USelectMultiplayWidget::NoButtonUnHovered()
{
    SetUnHovered();
}

void USelectMultiplayWidget::EnterButtonClicked()
{
    bIsMessageHandled = false;
    bIsHovered = false;
    MenuType = EMenuMultiPlayType::None;
    MessageBox01Hidden();

    UCanvasPanelSlot* MenuStartTextSlot = Cast<UCanvasPanelSlot>(MenuStartTextBox->Slot);
    if (MenuStartTextSlot)
    {
        MenuStartTextSlot->SetPosition(FVector2D(160.0f, -200.f));
    }
    UCanvasPanelSlot* SizeImageSlot = Cast<UCanvasPanelSlot>(MenuSizeImage->Slot);
    if (SizeImageSlot)
    {
        SizeImageSlot->SetPosition(FVector2D(0.f, -700.f));
    }

    MenuStartTextBox->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f)));
    MessageCheckTextBox02->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f)));
}

void USelectMultiplayWidget::EnterButtonHovered()
{
    bIsHovered = true;
    if (EMenuMultiPlayType::EnterCheck == MenuType)
    {
        return;
    }

    MessageCheckTextBox02->SetColorAndOpacity(FSlateColor(FLinearColor(0.15f, 0.5f, 0.52f, 1.0f)));
    MenuType = EMenuMultiPlayType::EnterCheck;
}

void USelectMultiplayWidget::EnterButtonUnHovered()
{
    SetUnHovered();
}

void USelectMultiplayWidget::MessageBox00Visible()
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

void USelectMultiplayWidget::MessageBox00Hidden()
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

void USelectMultiplayWidget::MessageBox01Visible()
{
    MessageImage->SetVisibility(ESlateVisibility::Visible);
    MessageTextBox->SetVisibility(ESlateVisibility::Visible);
    MessageCheckImage02->SetVisibility(ESlateVisibility::Visible);
    MessageCheckTextBox02->SetVisibility(ESlateVisibility::Visible);
    MessageCheckButton02->SetVisibility(ESlateVisibility::Visible);
}

void USelectMultiplayWidget::MessageBox01Hidden()
{
    MessageImage->SetVisibility(ESlateVisibility::Hidden);
    MessageTextBox->SetVisibility(ESlateVisibility::Hidden);
    MessageCheckImage02->SetVisibility(ESlateVisibility::Hidden);
    MessageCheckTextBox02->SetVisibility(ESlateVisibility::Hidden);
    MessageCheckButton02->SetVisibility(ESlateVisibility::Hidden);
}

void USelectMultiplayWidget::VariableSetting()
{
    if (MenuStartButton) // StartButton Setting
    {
        MenuStartButton->OnClicked.AddDynamic(this, &USelectMultiplayWidget::StartButtonClicked);
        MenuStartButton->OnHovered.AddDynamic(this, &USelectMultiplayWidget::StartButtonHovered);
        MenuStartButton->OnUnhovered.AddDynamic(this, &USelectMultiplayWidget::StartButtonUnHovered);

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

    if (MenuReadyButton) // ReadyButton Setting
    {
        MenuReadyButton->OnClicked.AddDynamic(this, &USelectMultiplayWidget::ReadyButtonClicked);
        MenuReadyButton->OnHovered.AddDynamic(this, &USelectMultiplayWidget::ReadyButtonHovered);
        MenuReadyButton->OnUnhovered.AddDynamic(this, &USelectMultiplayWidget::ReadyButtonUnHovered);

        UCanvasPanelSlot* SettingButtonSlot = Cast<UCanvasPanelSlot>(MenuReadyButton->Slot);
        if (SettingButtonSlot)
        {
            SettingButtonSlot->SetAnchors(FAnchors(0.0f, 0.5f));
            SettingButtonSlot->SetAlignment(FVector2D(0.0f, 0.5f));
            SettingButtonSlot->SetPosition(FVector2D(140.0f, -115.f));
            SettingButtonSlot->SetSize(FVector2D(330.f, 40.f));
        }
    }

    if (MenuExitButton) // ExitButton Setting
    {
        MenuExitButton->OnClicked.AddDynamic(this, &USelectMultiplayWidget::ExitButtonClicked);
        MenuExitButton->OnHovered.AddDynamic(this, &USelectMultiplayWidget::ExitButtonHovered);
        MenuExitButton->OnUnhovered.AddDynamic(this, &USelectMultiplayWidget::ExitButtonUnHovered);

        UCanvasPanelSlot* PrevButtonSlot = Cast<UCanvasPanelSlot>(MenuExitButton->Slot);
        if (PrevButtonSlot)
        {
            PrevButtonSlot->SetAnchors(FAnchors(0.0f, 0.5f));
            PrevButtonSlot->SetAlignment(FVector2D(0.0f, 0.5f));
            PrevButtonSlot->SetPosition(FVector2D(140.0f, -35.f));
            PrevButtonSlot->SetSize(FVector2D(330.f, 40.f));
        }
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

    UCanvasPanelSlot* MenuReadyTextSlot = Cast<UCanvasPanelSlot>(MenuReadyTextBox->Slot);
    if (MenuReadyTextSlot)
    {
        MenuReadyTextSlot->SetAnchors(FAnchors(0.0f, 0.5f));
        MenuReadyTextSlot->SetAlignment(FVector2D(0.0f, 0.5f));
        MenuReadyTextSlot->SetPosition(FVector2D(160.0f, -120.f));
        MenuReadyTextSlot->SetSize(FVector2D(400.f, 60.f));

        FSlateFontInfo FontInfo;
        FontInfo.FontObject = LoadObject<UObject>(nullptr, TEXT("/Game/Asset/Font/DMC5Font_Font"));
        FontInfo.TypefaceFontName = FName("Default");
        FontInfo.Size = 40;
        FontInfo.LetterSpacing = 100;

        MenuReadyTextBox->SetFont(FontInfo);
        MenuReadyTextBox->SetJustification(ETextJustify::Left);
        MenuReadyTextBox->SetText(FText::FromString(TEXT("Ready")));
        MenuReadyTextBox->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f)));
    }

    UCanvasPanelSlot* MenuExitTextSlot = Cast<UCanvasPanelSlot>(MenuExitTextBox->Slot);
    if (MenuExitTextSlot)
    {
        MenuExitTextSlot->SetAnchors(FAnchors(0.0f, 0.5f));
        MenuExitTextSlot->SetAlignment(FVector2D(0.0f, 0.5f));
        MenuExitTextSlot->SetPosition(FVector2D(160.0f, -40.f));
        MenuExitTextSlot->SetSize(FVector2D(400.f, 60.f));

        FSlateFontInfo FontInfo;
        FontInfo.FontObject = LoadObject<UObject>(nullptr, TEXT("/Game/Asset/Font/DMC5Font_Font"));
        FontInfo.TypefaceFontName = FName("Default");
        FontInfo.Size = 40;
        FontInfo.LetterSpacing = 100;

        MenuExitTextBox->SetFont(FontInfo);
        MenuExitTextBox->SetJustification(ETextJustify::Left);
        MenuExitTextBox->SetText(FText::FromString(TEXT("Exit")));
        MenuExitTextBox->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f)));
    }

    UCanvasPanelSlot* UserBackImageSlot = Cast<UCanvasPanelSlot>(UserBackImage->Slot);
    if (UserBackImageSlot)
    {
        UserBackImageSlot->SetAnchors(FAnchors(1.0f, 0.5f));
        UserBackImageSlot->SetAlignment(FVector2D(1.0f, 0.5f));
        UserBackImageSlot->SetPosition(FVector2D(0.f, 270.f));
        UserBackImageSlot->SetSize(FVector2D(800.f, 200.f));
    }

    UCanvasPanelSlot* UserImageSlot00 = Cast<UCanvasPanelSlot>(UserImage00->Slot);
    if (UserImageSlot00)
    {
        UserImageSlot00->SetAnchors(FAnchors(1.0f, 0.5f));
        UserImageSlot00->SetAlignment(FVector2D(1.0f, 0.5f));
        UserImageSlot00->SetPosition(FVector2D(-612.5f, 270.f));
        UserImageSlot00->SetSize(FVector2D(150.f, 140.f));
    }

    UCanvasPanelSlot* UserImageSlot01 = Cast<UCanvasPanelSlot>(UserImage01->Slot);
    if (UserImageSlot01)
    {
        UserImageSlot01->SetAnchors(FAnchors(1.0f, 0.5f));
        UserImageSlot01->SetAlignment(FVector2D(1.0f, 0.5f));
        UserImageSlot01->SetPosition(FVector2D(-420.f, 270.f));
        UserImageSlot01->SetSize(FVector2D(150.f, 140.f));
    }

    UCanvasPanelSlot* UserImageSlot02 = Cast<UCanvasPanelSlot>(UserImage02->Slot);
    if (UserImageSlot02)
    {
        UserImageSlot02->SetAnchors(FAnchors(1.0f, 0.5f));
        UserImageSlot02->SetAlignment(FVector2D(1.0f, 0.5f));
        UserImageSlot02->SetPosition(FVector2D(-227.5f, 270.f));
        UserImageSlot02->SetSize(FVector2D(150.f, 140.f));
    }

    UCanvasPanelSlot* UserImageSlot03 = Cast<UCanvasPanelSlot>(UserImage03->Slot);
    if (UserImageSlot03)
    {
        UserImageSlot03->SetAnchors(FAnchors(1.0f, 0.5f));
        UserImageSlot03->SetAlignment(FVector2D(1.0f, 0.5f));
        UserImageSlot03->SetPosition(FVector2D(-35.f, 270.f));
        UserImageSlot03->SetSize(FVector2D(150.f, 140.f));
    }

    UCanvasPanelSlot* UserTextSlot00 = Cast<UCanvasPanelSlot>(UserTextBox00->Slot);
    if (UserTextSlot00)
    {
        UserTextSlot00->SetAnchors(FAnchors(1.0f, 0.5f));
        UserTextSlot00->SetAlignment(FVector2D(1.0f, 0.5f));
        UserTextSlot00->SetPosition(FVector2D(-630.0f, 390.0));
        UserTextSlot00->SetSize(FVector2D(115, 40.f));

        FSlateFontInfo FontInfo;
        FontInfo.FontObject = LoadObject<UObject>(nullptr, TEXT("/Game/Asset/Font/DMC5Font_Font"));
        FontInfo.TypefaceFontName = FName("Default");
        // FontInfo.Size = 40;
        FontInfo.LetterSpacing = 100;

        UserTextBox00->SetFont(FontInfo);
        UserTextBox00->SetJustification(ETextJustify::Center);
        UserTextBox00->SetText(FText::FromString(TEXT("Ready")));
        UserTextBox00->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 0.7f, 0.0f, 1.0f)));
    }

    UCanvasPanelSlot* UserTextSlot01 = Cast<UCanvasPanelSlot>(UserTextBox01->Slot);
    if (UserTextSlot01)
    {
        UserTextSlot01->SetAnchors(FAnchors(1.0f, 0.5f));
        UserTextSlot01->SetAlignment(FVector2D(1.0f, 0.5f));
        UserTextSlot01->SetPosition(FVector2D(-437.5f, 390.0f));
        UserTextSlot01->SetSize(FVector2D(115, 40.f));

        FSlateFontInfo FontInfo;
        FontInfo.FontObject = LoadObject<UObject>(nullptr, TEXT("/Game/Asset/Font/DMC5Font_Font"));
        FontInfo.TypefaceFontName = FName("Default");
        // FontInfo.Size = 40;
        FontInfo.LetterSpacing = 100;

        UserTextBox01->SetFont(FontInfo);
        UserTextBox01->SetJustification(ETextJustify::Center);
        UserTextBox01->SetText(FText::FromString(TEXT("Ready")));
        UserTextBox01->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 0.7f, 0.0f, 1.0f)));
    }

    UCanvasPanelSlot* UserTextSlot02 = Cast<UCanvasPanelSlot>(UserTextBox02->Slot);
    if (UserTextSlot02)
    {
        UserTextSlot02->SetAnchors(FAnchors(1.0f, 0.5f));
        UserTextSlot02->SetAlignment(FVector2D(1.0f, 0.5f));
        UserTextSlot02->SetPosition(FVector2D(-243.5f, 390.0f));
        UserTextSlot02->SetSize(FVector2D(115, 40.f));

        FSlateFontInfo FontInfo;
        FontInfo.FontObject = LoadObject<UObject>(nullptr, TEXT("/Game/Asset/Font/DMC5Font_Font"));
        FontInfo.TypefaceFontName = FName("Default");
        // FontInfo.Size = 40;
        FontInfo.LetterSpacing = 100;

        UserTextBox02->SetFont(FontInfo);
        UserTextBox02->SetJustification(ETextJustify::Center);
        UserTextBox02->SetText(FText::FromString(TEXT("Ready")));
        UserTextBox02->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 0.7f, 0.0f, 1.0f)));
    }

    UCanvasPanelSlot* UserTextSlot03 = Cast<UCanvasPanelSlot>(UserTextBox03->Slot);
    if (UserTextSlot03)
    {
        UserTextSlot03->SetAnchors(FAnchors(1.0f, 0.5f));
        UserTextSlot03->SetAlignment(FVector2D(1.0f, 0.5f));
        UserTextSlot03->SetPosition(FVector2D(-51.5, 390.0f));
        UserTextSlot03->SetSize(FVector2D(115, 40.f));

        FSlateFontInfo FontInfo;
        FontInfo.FontObject = LoadObject<UObject>(nullptr, TEXT("/Game/Asset/Font/DMC5Font_Font"));
        FontInfo.TypefaceFontName = FName("Default");
        // FontInfo.Size = 40;
        FontInfo.LetterSpacing = 100;

        UserTextBox03->SetFont(FontInfo);
        UserTextBox03->SetJustification(ETextJustify::Center);
        UserTextBox03->SetText(FText::FromString(TEXT("Ready")));
        UserTextBox03->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 0.7f, 0.0f, 1.0f)));
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

        FSlateFontInfo FontInfo;
        FontInfo.FontObject = LoadObject<UObject>(nullptr, TEXT("/Game/Asset/Font/DMC5Font_Font"));
        FontInfo.TypefaceFontName = FName("Default");
        //FontInfo.Size = 38;
        //FontInfo.LetterSpacing = 0;

        MenuBarTextBox00->SetFont(FontInfo);
        MenuBarTextBox00->SetJustification(ETextJustify::Left);
        MenuBarTextBox00->SetText(FText::FromString(TEXT("INFORMATION")));
        MenuBarTextBox00->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f)));
    }

    UCanvasPanelSlot* MenuBarTextBoxSlot01 = Cast<UCanvasPanelSlot>(MenuBarTextBox01->Slot);
    if (MenuBarTextBoxSlot01)
    {
        MenuBarTextBoxSlot01->SetAnchors(FAnchors(1.0f, 0.5f));
        MenuBarTextBoxSlot01->SetAlignment(FVector2D(1.0f, 0.5f));
        MenuBarTextBoxSlot01->SetPosition(FVector2D(-595.0f, 120.f));
        MenuBarTextBoxSlot01->SetSize(FVector2D(165.0f, 40.f));

        FSlateFontInfo FontInfo;
        FontInfo.FontObject = LoadObject<UObject>(nullptr, TEXT("/Game/Asset/Font/DMC5Font_Font"));
        FontInfo.TypefaceFontName = FName("Default");
        //FontInfo.Size = 38;
        //FontInfo.LetterSpacing = 0;

        MenuBarTextBox01->SetFont(FontInfo);
        MenuBarTextBox01->SetJustification(ETextJustify::Left);
        MenuBarTextBox01->SetText(FText::FromString(TEXT("CONNECTED")));
        MenuBarTextBox01->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f)));
    }

    UCanvasPanelSlot* MenuBarTextBoxSlot02 = Cast<UCanvasPanelSlot>(MenuBarTextBox02->Slot);
    if (MenuBarTextBoxSlot02)
    {
        MenuBarTextBoxSlot02->SetAnchors(FAnchors(1.0f, 0.5f));
        MenuBarTextBoxSlot02->SetAlignment(FVector2D(1.0f, 0.5f));
        MenuBarTextBoxSlot02->SetPosition(FVector2D(-231.0f, -58.0f));
        MenuBarTextBoxSlot02->SetSize(FVector2D(528.0f, 40.f));

        FSlateFontInfo FontInfo;
        FontInfo.FontObject = LoadObject<UObject>(nullptr, TEXT("/Game/Asset/Font/DMC5Font_Font"));
        FontInfo.TypefaceFontName = FName("Default");
        //FontInfo.Size = 38;
        //FontInfo.LetterSpacing = 0;

        MenuBarTextBox02->SetFont(FontInfo);
        MenuBarTextBox02->SetJustification(ETextJustify::Left);
        MenuBarTextBox02->SetText(FText::FromString(TEXT("Local IP : -")));
        MenuBarTextBox02->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f)));
    }

    UCanvasPanelSlot* MenuBarTextBoxSlot03 = Cast<UCanvasPanelSlot>(MenuBarTextBox03->Slot);
    if (MenuBarTextBoxSlot03)
    {
        MenuBarTextBoxSlot03->SetAnchors(FAnchors(1.0f, 0.5f));
        MenuBarTextBoxSlot03->SetAlignment(FVector2D(1.0f, 0.5f));
        MenuBarTextBoxSlot03->SetPosition(FVector2D(-595.0f, 42.0f));
        MenuBarTextBoxSlot03->SetSize(FVector2D(165.0f, 40.f));

        FSlateFontInfo FontInfo;
        FontInfo.FontObject = LoadObject<UObject>(nullptr, TEXT("/Game/Asset/Font/DMC5Font_Font"));
        FontInfo.TypefaceFontName = FName("Default");
        //FontInfo.Size = 38;
        //FontInfo.LetterSpacing = 0;

        MenuBarTextBox03->SetFont(FontInfo);
        MenuBarTextBox03->SetJustification(ETextJustify::Left);
        MenuBarTextBox03->SetText(FText::FromString(TEXT("Players : ")));
        MenuBarTextBox03->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f)));
    }

    UCanvasPanelSlot* MenuBarTextBoxSlot04 = Cast<UCanvasPanelSlot>(MenuBarTextBox04->Slot);
    if (MenuBarTextBoxSlot04)
    {
        MenuBarTextBoxSlot04->SetAnchors(FAnchors(1.0f, 0.5f));
        MenuBarTextBoxSlot04->SetAlignment(FVector2D(1.0f, 0.5f));
        MenuBarTextBoxSlot04->SetPosition(FVector2D(-231.0f, -8.0f));
        MenuBarTextBoxSlot04->SetSize(FVector2D(528.0f, 40.f));

        FSlateFontInfo FontInfo;
        FontInfo.FontObject = LoadObject<UObject>(nullptr, TEXT("/Game/Asset/Font/DMC5Font_Font"));
        FontInfo.TypefaceFontName = FName("Default");
        //FontInfo.Size = 38;
        //FontInfo.LetterSpacing = 0;

        MenuBarTextBox04->SetFont(FontInfo);
        MenuBarTextBox04->SetJustification(ETextJustify::Left);
        MenuBarTextBox04->SetText(FText::FromString(TEXT("Public IP : -")));
        MenuBarTextBox04->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f)));
    }

    UCanvasPanelSlot* MessageImageSlot = Cast<UCanvasPanelSlot>(MessageImage->Slot);
    if (MessageImageSlot)
    {
        MessageImageSlot->SetAnchors(FAnchors(0.5f, 0.5f));
        MessageImageSlot->SetAlignment(FVector2D(0.5f, 0.5f));
        MessageImageSlot->SetPosition(FVector2D(0.0f, 0.0f));
        MessageImageSlot->SetSize(FVector2D(620.0f, 200.f));
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
        MessageTextBox->SetText(FText::FromString(TEXT("Are you sure leave the room?")));
        MessageTextBox->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f)));
    }

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

        MessageCheckButton00->OnClicked.AddDynamic(this, &USelectMultiplayWidget::YesButtonClicked);
        MessageCheckButton00->OnHovered.AddDynamic(this, &USelectMultiplayWidget::YesButtonHovered);
        MessageCheckButton00->OnUnhovered.AddDynamic(this, &USelectMultiplayWidget::YesButtonUnHovered);
    }

    UCanvasPanelSlot* MessageCheckButtonSlot01 = Cast<UCanvasPanelSlot>(MessageCheckButton01->Slot);
    if (MessageCheckButtonSlot01)
    {
        MessageCheckButtonSlot01->SetAnchors(FAnchors(0.5f, 0.5f));
        MessageCheckButtonSlot01->SetAlignment(FVector2D(0.5f, 0.5f));
        MessageCheckButtonSlot01->SetPosition(FVector2D(140.f, 35.0f));
        MessageCheckButtonSlot01->SetSize(FVector2D(200.0f, 60.0f));

        MessageCheckButton01->OnClicked.AddDynamic(this, &USelectMultiplayWidget::NoButtonClicked);
        MessageCheckButton01->OnHovered.AddDynamic(this, &USelectMultiplayWidget::NoButtonHovered);
        MessageCheckButton01->OnUnhovered.AddDynamic(this, &USelectMultiplayWidget::NoButtonUnHovered);
    }

    UCanvasPanelSlot* MessageCheckImageSlot02 = Cast<UCanvasPanelSlot>(MessageCheckImage02->Slot);
    if (MessageCheckImageSlot02)
    {
        MessageCheckImageSlot02->SetAnchors(FAnchors(0.5f, 0.5f));
        MessageCheckImageSlot02->SetAlignment(FVector2D(0.5f, 0.5f));
        MessageCheckImageSlot02->SetPosition(FVector2D(0.0f, 35.0f));
        MessageCheckImageSlot02->SetSize(FVector2D(200.0f, 60.0f));
    }

    UCanvasPanelSlot* MessageCheckTextBoxSlot02 = Cast<UCanvasPanelSlot>(MessageCheckTextBox02->Slot);
    if (MessageCheckTextBoxSlot02)
    {
        MessageCheckTextBoxSlot02->SetAnchors(FAnchors(0.5f, 0.5f));
        MessageCheckTextBoxSlot02->SetAlignment(FVector2D(0.5f, 0.5f));
        MessageCheckTextBoxSlot02->SetPosition(FVector2D(0.0f, 37.0f));
        MessageCheckTextBoxSlot02->SetSize(FVector2D(200.0f, 54.f));

        MessageCheckTextBox02->SetJustification(ETextJustify::Center);
        MessageCheckTextBox02->SetText(FText::FromString(TEXT("OK")));
        MessageCheckTextBox02->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f)));
    }

    UCanvasPanelSlot* MessageCheckButtonSlot02 = Cast<UCanvasPanelSlot>(MessageCheckButton02->Slot);
    if (MessageCheckButtonSlot02)
    {
        MessageCheckButtonSlot02->SetAnchors(FAnchors(0.5f, 0.5f));
        MessageCheckButtonSlot02->SetAlignment(FVector2D(0.5f, 0.5f));
        MessageCheckButtonSlot02->SetPosition(FVector2D(0.0f, 35.0f));
        MessageCheckButtonSlot02->SetSize(FVector2D(200.0f, 60.0f));

        MessageCheckButton02->OnClicked.AddDynamic(this, &USelectMultiplayWidget::EnterButtonClicked);
        MessageCheckButton02->OnHovered.AddDynamic(this, &USelectMultiplayWidget::EnterButtonHovered);
        MessageCheckButton02->OnUnhovered.AddDynamic(this, &USelectMultiplayWidget::EnterButtonUnHovered);
    }


    PlayerSlots.Add(UserImage00);
    PlayerSlots.Add(UserImage01);
    PlayerSlots.Add(UserImage02);
    PlayerSlots.Add(UserImage03);

    PlayerReadyTexts.Add(UserTextBox00);
    PlayerReadyTexts.Add(UserTextBox01);
    PlayerReadyTexts.Add(UserTextBox02);
    PlayerReadyTexts.Add(UserTextBox03);

    MessageBox00Hidden();
    MessageBox01Hidden();
}