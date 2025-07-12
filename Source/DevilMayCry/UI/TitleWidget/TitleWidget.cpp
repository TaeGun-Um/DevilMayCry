// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SizeBox.h"
#include "Components/Image.h"

bool UTitleWidget::Initialize()
{
    Super::Initialize();

    if (TitleStartButton) // Start Button 함수 바인딩
    {
        TitleStartButton->OnClicked.AddDynamic(this, &UTitleWidget::OnStartClicked);
    }

    if (TitleExitButton) // Exit Button 함수 바인딩
    {
        TitleExitButton->OnClicked.AddDynamic(this, &UTitleWidget::OnExitClicked);
    }

    TitleSizeBox1->SetVisibility(ESlateVisibility::Hidden);
    TitleSizeBox2->SetVisibility(ESlateVisibility::Hidden);
    TitleStartButton->SetVisibility(ESlateVisibility::Hidden);
    TitleExitButton->SetVisibility(ESlateVisibility::Hidden);

    return true;
}

void UTitleWidget::PlayAnim()
{
    PlayAnimation(BlinkAnimation, 0.f, 0); // 0은 무한 반복
}

void UTitleWidget::OnStartClicked()
{
    UGameplayStatics::OpenLevel(this, TEXT("Location2"));
}

void UTitleWidget::OnExitClicked()
{
    UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, true);
}

void UTitleWidget::StopBlinkAnimation()
{
    if (IsAnimationPlaying(BlinkAnimation))
    {
        StopAnimation(BlinkAnimation);
    }

    TitleSizeBox3->SetVisibility(ESlateVisibility::Hidden);
    TitleAnyKeyImage->SetVisibility(ESlateVisibility::Hidden);

    TitleSizeBox1->SetVisibility(ESlateVisibility::Visible);
    TitleSizeBox2->SetVisibility(ESlateVisibility::Visible);
    TitleStartButton->SetVisibility(ESlateVisibility::Visible);
    TitleExitButton->SetVisibility(ESlateVisibility::Visible);
}