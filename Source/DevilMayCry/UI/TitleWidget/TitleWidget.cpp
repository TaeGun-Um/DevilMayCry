// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

bool UTitleWidget::Initialize()
{
    Super::Initialize();

    if (TitleStartButton) // Start Button �Լ� ���ε�
    {
        TitleStartButton->OnClicked.AddDynamic(this, &UTitleWidget::OnStartClicked);
    }

    if (TitleExitButton) // Exit Button �Լ� ���ε�
    {
        TitleExitButton->OnClicked.AddDynamic(this, &UTitleWidget::OnExitClicked);
    }

    return true;
}

void UTitleWidget::OnStartClicked()
{
    UGameplayStatics::OpenLevel(this, TEXT("Location2"));
}

void UTitleWidget::OnExitClicked()
{
    UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, true);
}
