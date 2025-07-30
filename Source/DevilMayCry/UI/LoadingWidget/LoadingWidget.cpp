// Fill out your copyright notice in the Description page of Project Settings.


#include "LoadingWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

bool ULoadingWidget::Initialize()
{
    Super::Initialize();
    VariableSetting();

    return false;
}

void ULoadingWidget::ArrowClicked()
{
    LoadingTextBox->SetText(FText::FromString(StringSlot[Index++]));

    if (StringSlot.Num() == Index)
    {
        Index = 0;
    }
}

void ULoadingWidget::ArrowHovered()
{

}

void ULoadingWidget::ArrowUnHovered()
{

}

void ULoadingWidget::VariableSetting()
{
    LoadingArrowButton->OnClicked.AddDynamic(this, &ULoadingWidget::ArrowClicked);
    LoadingArrowButton->OnHovered.AddDynamic(this, &ULoadingWidget::ArrowHovered);
    LoadingArrowButton->OnUnhovered.AddDynamic(this, &ULoadingWidget::ArrowUnHovered);

    StringSlot.Add(TEXT("Test1"));
    StringSlot.Add(TEXT("Test2"));
    StringSlot.Add(TEXT("Test3"));
    StringSlot.Add(TEXT("Test4"));
    StringSlot.Add(TEXT("Test5"));
    StringSlot.Add(TEXT("Test6"));
    StringSlot.Add(TEXT("Test7"));
}
