// Fill out your copyright notice in the Description page of Project Settings.


#include "EndingWidget.h"
#include "Components/Image.h"

bool UEndingWidget::Initialize()
{
    Super::Initialize();
    VariableSetting();

    return true;
}

void UEndingWidget::SetCapturedTexture(UTexture2D* _Tex)
{
    if (_Tex && EndingImage)
    {
        FSlateBrush Brush;
        Brush.SetResourceObject(_Tex);
        Brush.ImageSize = FVector2D(_Tex->GetSizeX(), _Tex->GetSizeY());
        EndingImage->SetBrush(Brush);
    }
}

void UEndingWidget::VariableSetting()
{

}

