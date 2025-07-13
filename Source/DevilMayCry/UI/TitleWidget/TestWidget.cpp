// Fill out your copyright notice in the Description page of Project Settings.


#include "TestWidget.h"
#include "Components/Button.h"
#include "Components/SizeBox.h"
#include "Components/Image.h"
#include "Components/SizeBoxSlot.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Blueprint/WidgetLayoutLibrary.h"
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

        UCanvasPanelSlot* ButtonSlot0 = Cast<UCanvasPanelSlot>(TestButton0->Slot);
        if (ButtonSlot0)
        {
            ButtonSlot0->SetAnchors(FAnchors(0.5f, 0.5f));
            ButtonSlot0->SetAlignment(FVector2D(0.5f, 0.5f));
            ButtonSlot0->SetPosition(FVector2D(0.0f, 90.f));
            ButtonSlot0->SetSize(FVector2D(300.f, 50.f));
        }
    }
    if (TestButton1)
    {
        TestButton1->OnHovered.AddDynamic(this, &UTestWidget::Button1Hover);
        TestButton1->OnUnhovered.AddDynamic(this, &UTestWidget::Button1UnHover);
        UCanvasPanelSlot* ButtonSlot1 = Cast<UCanvasPanelSlot>(TestButton1->Slot);
        if (ButtonSlot1)
        {
            ButtonSlot1->SetAnchors(FAnchors(0.5f, 0.5f));
            ButtonSlot1->SetAlignment(FVector2D(0.5f, 0.5f));
            ButtonSlot1->SetPosition(FVector2D(0.0f, 160.f));
            ButtonSlot1->SetSize(FVector2D(300.f, 50.f));
        }
    }
    if (TestButton2)
    {
        TestButton2->OnHovered.AddDynamic(this, &UTestWidget::Button2Hover);
        TestButton2->OnUnhovered.AddDynamic(this, &UTestWidget::Button2UnHover);
        UCanvasPanelSlot* ButtonSlot2 = Cast<UCanvasPanelSlot>(TestButton2->Slot);
        if (ButtonSlot2)
        {
            ButtonSlot2->SetAnchors(FAnchors(0.5f, 0.5f));
            ButtonSlot2->SetAlignment(FVector2D(0.5f, 0.5f));
            ButtonSlot2->SetPosition(FVector2D(0.0f, 230.f));
            ButtonSlot2->SetSize(FVector2D(300.f, 50.f));
        }
    }

    UCanvasPanelSlot* SizeImageSlot = Cast<UCanvasPanelSlot>(TestSizeImage->Slot);
    if (SizeImageSlot)
    {
        SizeImageSlot->SetAnchors(FAnchors(0.5f, 0.5f));            // 버튼 중심 기준
        SizeImageSlot->SetAlignment(FVector2D(0.5f, 0.5f));         // 중심 정렬
        SizeImageSlot->SetOffsets(FMargin(0.f, -700.f, 300.f, 50.f)); // 초기폭 설정
    }

    MenuType = ETitleMenuType::None;
    
    return true;
}

void UTestWidget::Button0Hover()
{
    if (ETitleMenuType::MainMenu == MenuType)
    {
        return;
    }

    MenuType = ETitleMenuType::MainMenu;

    UCanvasPanelSlot* ButtonSlot0 = Cast<UCanvasPanelSlot>(TestButton0->Slot);
    if (ButtonSlot0)
    {
        FVector2D CurPos = ButtonSlot0->GetPosition();
        UCanvasPanelSlot* SizeSlot = Cast<UCanvasPanelSlot>(TestSizeImage->Slot);
        if (SizeSlot)
        {
            SizeSlot->SetPosition(CurPos);
        }
    }

    PlayAnimation(SizeUpAnimation);
}
void UTestWidget::Button0UnHover()
{
    int a = 0;
}

void UTestWidget::Button1Hover()
{
    if (ETitleMenuType::Exit == MenuType)
    {
        return;
    }

    MenuType = ETitleMenuType::Exit;

    UCanvasPanelSlot* ButtonSlot1 = Cast<UCanvasPanelSlot>(TestButton1->Slot);
    if (ButtonSlot1)
    {
        FVector2D CurPos = ButtonSlot1->GetPosition();
        UCanvasPanelSlot* SizeSlot = Cast<UCanvasPanelSlot>(TestSizeImage->Slot);
        if (SizeSlot)
        {
            SizeSlot->SetPosition(CurPos);
        }
    }

    PlayAnimation(SizeUpAnimation);
}
void UTestWidget::Button1UnHover()
{
    int a = 0;
}

void UTestWidget::Button2Hover()
{
    if (ETitleMenuType::Setting == MenuType)
    {
        return;
    }

    MenuType = ETitleMenuType::Setting;

    UCanvasPanelSlot* ButtonSlot2 = Cast<UCanvasPanelSlot>(TestButton2->Slot);
    if (ButtonSlot2)
    {
        FVector2D CurPos = ButtonSlot2->GetPosition();
        UCanvasPanelSlot* SizeSlot = Cast<UCanvasPanelSlot>(TestSizeImage->Slot);
        if (SizeSlot)
        {
            SizeSlot->SetPosition(CurPos);
        }
    }

    PlayAnimation(SizeUpAnimation);
}
void UTestWidget::Button2UnHover()
{
    int a = 0;
}