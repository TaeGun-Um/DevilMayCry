// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectMenuWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/CanvasPanelSlot.h"

bool USelectMenuWidget::Initialize()
{
    Super::Initialize();
    VariableSetting();

	return true;
}

void USelectMenuWidget::PlayFadeAnimation()
{
	PlayAnimation(FadeAnimation);
}

void USelectMenuWidget::StartButtonClicked()
{
    // UGameplayStatics::OpenLevel(this, TEXT("Location2"));
    UGameplayStatics::OpenLevel(this, FName(TEXT("/Game/Scene/Location2")));
    // GetWorld()->ServerTravel(TEXT("/Game/Scene/Location2?listen"), false);
}

void USelectMenuWidget::StartButtonHovered()
{
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
}

void USelectMenuWidget::StartButtonUnHovered()
{
}

void USelectMenuWidget::SettingButtonClicked()
{
}

void USelectMenuWidget::SettingButtonHovered()
{
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
}

void USelectMenuWidget::SettingButtonUnHovered()
{
}

void USelectMenuWidget::PrevButtonClicked()
{
}

void USelectMenuWidget::PrevButtonHovered()
{
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
}

void USelectMenuWidget::PrevButtonUnHovered()
{
}

EMenuType USelectMenuWidget::GetMenuType()
{
    return MenuType;
}

void USelectMenuWidget::SetUnHovered()
{
    bIsHovered = false;
}

bool USelectMenuWidget::IsButtonHovered()
{
    return bIsHovered;
}

void USelectMenuWidget::SetIsEnd()
{
    bIsEnd = true;
}

bool USelectMenuWidget::GetIsEnd()
{
    return bIsEnd;
}

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
        MenuSettingTextBox->SetText(FText::FromString(TEXT("Setting")));
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
}
