// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"
#include "Components/SizeBox.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/CanvasPanelSlot.h"

bool UTitleWidget::Initialize()
{
    Super::Initialize();
    VariableSetting();

    MenuType = ETitleMenuType::None;

    // Before Activated, Hidden
    TitleStartButton->SetVisibility(ESlateVisibility::Hidden);
    TitleExitButton->SetVisibility(ESlateVisibility::Hidden);
    MainMenuTextBox->SetVisibility(ESlateVisibility::Hidden);
    ExitTextBox->SetVisibility(ESlateVisibility::Hidden);

    bIsHovered = false;
    bIsEnd = false;

    return true;
}

void UTitleWidget::StartButtonClicked()
{
    MenuType = ETitleMenuType::None;

    TitleTextBox->SetText(FText::FromString(TEXT("")));
    MainMenuTextBox->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f)));
    ExitTextBox->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f)));

    TitleAnyKeyImage->SetVisibility(ESlateVisibility::Visible);
    TitleStartButton->SetVisibility(ESlateVisibility::Hidden);
    TitleExitButton->SetVisibility(ESlateVisibility::Hidden);
    MainMenuTextBox->SetVisibility(ESlateVisibility::Hidden);
    ExitTextBox->SetVisibility(ESlateVisibility::Hidden);

    UCanvasPanelSlot* SizeImageSlot = Cast<UCanvasPanelSlot>(TitleSizeImage->Slot);
    if (SizeImageSlot)
    {
        SizeImageSlot->SetOffsets(FMargin(0.f, -700.f, 300.f, 60.f));
    }

    bIsEnd = true;
}

void UTitleWidget::StartButtonHovered()
{
    bIsHovered = true;
    TitleTextBox->SetText(FText::FromString(TEXT("Start the game")));
    if (ETitleMenuType::MainMenu == MenuType)
    {
        return;
    }

    MenuType = ETitleMenuType::MainMenu;
    MainMenuTextBox->SetColorAndOpacity(FSlateColor(FLinearColor(0.15f, 0.5f, 0.52f, 1.0f)));
    ExitTextBox->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f)));

    // Move SizeImage when hovering
    UCanvasPanelSlot* StartButtonSlot = Cast<UCanvasPanelSlot>(TitleStartButton->Slot);
    if (StartButtonSlot)
    {
        FVector2D CurPos = StartButtonSlot->GetPosition();
        UCanvasPanelSlot* SizeSlot = Cast<UCanvasPanelSlot>(TitleSizeImage->Slot);
        if (SizeSlot)
        {
            SizeSlot->SetPosition(CurPos);
        }
    }

    PlayAnimation(SizeUpAnimation);
}

void UTitleWidget::StartButtonUnHovered()
{
    SetUnHovered();
}

void UTitleWidget::ExitButtonClicked()
{
    UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, true);
}

void UTitleWidget::ExitButtonHovered()
{
    bIsHovered = true;
    TitleTextBox->SetText(FText::FromString(TEXT("Exit the game")));
    if (ETitleMenuType::Exit == MenuType)
    {
        return;
    }

    MenuType = ETitleMenuType::Exit;
    MainMenuTextBox->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f)));
    ExitTextBox->SetColorAndOpacity(FSlateColor(FLinearColor(0.15f, 0.5f, 0.52f, 1.0f)));

    // Move SizeImage when hovering
    UCanvasPanelSlot* ExitButtonSlot = Cast<UCanvasPanelSlot>(TitleExitButton->Slot);
    if (ExitButtonSlot)
    {
        FVector2D CurPos = ExitButtonSlot->GetPosition();
        UCanvasPanelSlot* SizeSlot = Cast<UCanvasPanelSlot>(TitleSizeImage->Slot);
        if (SizeSlot)
        {
            SizeSlot->SetPosition(CurPos);
        }
    }

    PlayAnimation(SizeUpAnimation);
}

void UTitleWidget::ExitButtonUnHovered()
{
    SetUnHovered();
}

void UTitleWidget::StopBlinkAnimation()
{
     if (IsAnimationPlaying(BlinkAnimation))
     {
         StopAnimation(BlinkAnimation);
     }

    TitleAnyKeyImage->SetVisibility(ESlateVisibility::Hidden);
}

void UTitleWidget::SetVisibileButton()
{
    TitleStartButton->SetVisibility(ESlateVisibility::Visible);
    TitleExitButton->SetVisibility(ESlateVisibility::Visible);
    MainMenuTextBox->SetVisibility(ESlateVisibility::Visible);
    ExitTextBox->SetVisibility(ESlateVisibility::Visible);
}

void UTitleWidget::VariableSetting()
{
    if (TitleAnyKeyImage) // Anykey Image Setting
    {
        UCanvasPanelSlot* AnikeyImageSlot = Cast<UCanvasPanelSlot>(TitleAnyKeyImage->Slot);
        if (AnikeyImageSlot)
        {
            AnikeyImageSlot->SetAnchors(FAnchors(0.5f, 0.5f)); // Button Center Ref.
            AnikeyImageSlot->SetAlignment(FVector2D(0.5f, 0.5f)); // Alignment
            AnikeyImageSlot->SetPosition(FVector2D(0.0f, 180.f));
            AnikeyImageSlot->SetSize(FVector2D(450.f, 75.f));
        }
    }

    if (TitleStartButton) // StartButton Setting
    {
        TitleStartButton->OnClicked.AddDynamic(this, &UTitleWidget::StartButtonClicked);
        TitleStartButton->OnHovered.AddDynamic(this, &UTitleWidget::StartButtonHovered);
        TitleStartButton->OnUnhovered.AddDynamic(this, &UTitleWidget::StartButtonUnHovered);

        UCanvasPanelSlot* StartButtonSlot = Cast<UCanvasPanelSlot>(TitleStartButton->Slot);
        if (StartButtonSlot)
        {
            StartButtonSlot->SetAnchors(FAnchors(0.5f, 0.5f)); // Button Center Ref.
            StartButtonSlot->SetAlignment(FVector2D(0.5f, 0.5f)); // Alignment
            StartButtonSlot->SetPosition(FVector2D(0.0f, 190.f));
            StartButtonSlot->SetSize(FVector2D(300.f, 60.f));
        }

        TitleStartButton->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 0.0f));
    }

    if (TitleExitButton) // ExitButton Setting
    {
        TitleExitButton->OnClicked.AddDynamic(this, &UTitleWidget::ExitButtonClicked);
        TitleExitButton->OnHovered.AddDynamic(this, &UTitleWidget::ExitButtonHovered);
        TitleExitButton->OnUnhovered.AddDynamic(this, &UTitleWidget::ExitButtonUnHovered);

        UCanvasPanelSlot* ExitButtonSlot = Cast<UCanvasPanelSlot>(TitleExitButton->Slot);
        if (ExitButtonSlot)
        {
            ExitButtonSlot->SetAnchors(FAnchors(0.5f, 0.5f));
            ExitButtonSlot->SetAlignment(FVector2D(0.5f, 0.5f));
            ExitButtonSlot->SetPosition(FVector2D(0.0f, 260.f));
            ExitButtonSlot->SetSize(FVector2D(300.f, 60.f));
        }

        TitleExitButton->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 0.0f));
    }

    // TitleSizeUpImage Setting
    UCanvasPanelSlot* SizeImageSlot = Cast<UCanvasPanelSlot>(TitleSizeImage->Slot);
    if (SizeImageSlot)
    {
        SizeImageSlot->SetAnchors(FAnchors(0.5f, 0.5f));
        SizeImageSlot->SetAlignment(FVector2D(0.5f, 0.5f));
        SizeImageSlot->SetOffsets(FMargin(0.f, -700.f, 300.f, 60.f)); // Initial settings : Position, Size(Width, Height)
    }

    // TitleTextBox Setting
    UCanvasPanelSlot* TextSlot = Cast<UCanvasPanelSlot>(TitleTextBox->Slot);
    if (TextSlot)
    {
        TextSlot->SetAnchors(FAnchors(0.5f, 0.5f));
        TextSlot->SetAlignment(FVector2D(0.5f, 0.5f));
        TextSlot->SetPosition(FVector2D(0.0f, 380.f));
        TextSlot->SetSize(FVector2D(700.f, 45.f));
        TitleTextBox->SetText(FText::FromString(TEXT("")));
    }

    // TitleTextBox Setting
    UCanvasPanelSlot* StartTextSlot = Cast<UCanvasPanelSlot>(MainMenuTextBox->Slot);
    if (StartTextSlot)
    {
        StartTextSlot->SetAnchors(FAnchors(0.5f, 0.5f)); // Button Center Ref.
        StartTextSlot->SetAlignment(FVector2D(0.5f, 0.5f)); // Alignment
        StartTextSlot->SetPosition(FVector2D(0.0f, 180.f));
        StartTextSlot->SetSize(FVector2D(300.f, 50.f));

        FSlateFontInfo FontInfo;
        FontInfo.FontObject = LoadObject<UObject>(nullptr, TEXT("/Game/Asset/Font/DMC5Font_Font"));
        FontInfo.TypefaceFontName = FName("Default");
        FontInfo.Size = 40;
        FontInfo.LetterSpacing = 100;

        MainMenuTextBox->SetFont(FontInfo);
        MainMenuTextBox->SetJustification(ETextJustify::Center);
        MainMenuTextBox->SetText(FText::FromString(TEXT("Main Menu")));
    }

    // TitleTextBox Setting
    UCanvasPanelSlot* ExitTextSlot = Cast<UCanvasPanelSlot>(ExitTextBox->Slot);
    if (ExitTextSlot)
    {
        ExitTextSlot->SetAnchors(FAnchors(0.5f, 0.5f)); // Button Center Ref.
        ExitTextSlot->SetAlignment(FVector2D(0.5f, 0.5f)); // Alignment
        ExitTextSlot->SetPosition(FVector2D(0.0f, 250.f));
        ExitTextSlot->SetSize(FVector2D(300.f, 50.f));

        FSlateFontInfo FontInfo;
        FontInfo.FontObject = LoadObject<UObject>(nullptr, TEXT("/Game/Asset/Font/DMC5Font_Font"));
        FontInfo.TypefaceFontName = FName("Default");
        FontInfo.Size = 40;
        FontInfo.LetterSpacing = 100;

        ExitTextBox->SetFont(FontInfo);
        ExitTextBox->SetJustification(ETextJustify::Center);
        ExitTextBox->SetText(FText::FromString(TEXT("Exit")));
    }
}