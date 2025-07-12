// Fill out your copyright notice in the Description page of Project Settings.


#include "TestWidget.h"
#include "Components/Button.h"
// #include "Kismet/GameplayStatics.h"

bool UTestWidget::Initialize()
{
    if (!Super::Initialize())
    {
        return false;
    }

    if (TestButton0)
    {
        TestButton0->OnHovered.AddDynamic(this, &UTestWidget::Button0Hover);
        TestButton0->OnUnhovered.AddDynamic(this, &UTestWidget::Button0UnHover);
    }
    if (TestButton1)
    {
        TestButton1->OnHovered.AddDynamic(this, &UTestWidget::Button1Hover);
        TestButton1->OnUnhovered.AddDynamic(this, &UTestWidget::Button1UnHover);
    }

	return true;
}

void UTestWidget::Button0Hover()
{
    // 호버 시 해당 위치에 좌우 사이즈로 커지는 박스 출현
    int a = 0;
}
void UTestWidget::Button0UnHover()
{
    // 언호버 시 해당 위치에 좌우 사이즈로 작아지는 박스 출현
    int a = 0;
}

void UTestWidget::Button1Hover()
{
    int a = 0;
}
void UTestWidget::Button1UnHover()
{
    int a = 0;
}