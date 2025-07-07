// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleSceneWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

bool UTitleSceneWidget::Initialize()
{
    Super::Initialize();

    if (TitleStartButton) // Start Button �Լ� ���ε�
    {
        TitleStartButton->OnClicked.AddDynamic(this, &UTitleSceneWidget::OnStartClicked);
    }

    if (TitleExitButton) // Exit Button �Լ� ���ε�
    {
        TitleExitButton->OnClicked.AddDynamic(this, &UTitleSceneWidget::OnExitClicked);
    }

    return true;
}

void UTitleSceneWidget::OnStartClicked()
{
    UGameplayStatics::OpenLevel(this, TEXT("Location2"));
}

void UTitleSceneWidget::OnExitClicked()
{
    UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, true);
}
