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
            StartButtonSlot->SetPosition(FVector2D(0.0f, 160.f));
            StartButtonSlot->SetSize(FVector2D(300.f, 50.f));
        }
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
            ExitButtonSlot->SetPosition(FVector2D(0.0f, 230.f));
            ExitButtonSlot->SetSize(FVector2D(300.f, 50.f));
        }
    }

    // TitleSizeUpImage Setting
    UCanvasPanelSlot* SizeImageSlot = Cast<UCanvasPanelSlot>(TitleSizeImage->Slot);
    if (SizeImageSlot)
    {
        SizeImageSlot->SetAnchors(FAnchors(0.5f, 0.5f)); 
        SizeImageSlot->SetAlignment(FVector2D(0.5f, 0.5f));
        SizeImageSlot->SetOffsets(FMargin(0.f, -700.f, 300.f, 50.f)); // Initial settings : Position, Size(Width, Height)
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

    MenuType = ETitleMenuType::None;

    // Before Activated, Hidden
    TitleStartButton->SetVisibility(ESlateVisibility::Hidden);
    TitleExitButton->SetVisibility(ESlateVisibility::Hidden);

    bIsHovered = false;
    bIsEnd = false;

    return true;
}

void UTitleWidget::PlayBlinkAnimation()
{
    PlayAnimation(BlinkAnimation, 0.f, 0); // 0 is infinite-loop
}

void UTitleWidget::StartButtonClicked()
{
    SetIsEnd();
    // UGameplayStatics::OpenLevel(this, TEXT("Location2"));
    SetVisibility(ESlateVisibility::Hidden);
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
    // PlayAnimation(SizeDownAnimation);
    // TitleTextBox->SetText(FText::FromString(TEXT("")));
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
    // PlayAnimation(SizeDownAnimation);
    // TitleTextBox->SetText(FText::FromString(TEXT("")));
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
}

ETitleMenuType UTitleWidget::GetMenuType()
{
    return MenuType;
}

void UTitleWidget::SetUnHovered()
{
    bIsHovered = false;
}

bool UTitleWidget::IsButtonHovered()
{
    return bIsHovered;
}

void UTitleWidget::SetIsEnd()
{
    bIsEnd = true;
}

bool UTitleWidget::GetIsEnd()
{
    return bIsEnd;
}
