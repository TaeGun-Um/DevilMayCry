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
    // ȣ�� �� �ش� ��ġ�� �¿� ������� Ŀ���� �ڽ� ����
    int a = 0;
}
void UTestWidget::Button0UnHover()
{
    // ��ȣ�� �� �ش� ��ġ�� �¿� ������� �۾����� �ڽ� ����
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