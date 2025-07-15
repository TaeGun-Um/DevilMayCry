// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectMenuWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/CanvasPanelSlot.h"

bool USelectMenuWidget::Initialize()
{
	if (false == Super::Initialize())
	{
		return false;
	}

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

	return true;
}

void USelectMenuWidget::PlayFadeAnimation()
{
	PlayAnimation(FadeAnimation);
}

void USelectMenuWidget::StartButtonClicked()
{
    UGameplayStatics::OpenLevel(this, TEXT("Location2"));
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