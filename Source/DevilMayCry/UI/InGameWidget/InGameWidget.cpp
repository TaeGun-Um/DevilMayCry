// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameWidget.h"
#include "Components/Image.h"

bool UInGameWidget::Initialize()
{
	Super::Initialize();
	VariableSetting();

	return true;
}

void UInGameWidget::UpdateBossHPBar(float CurHP, float MaxHP)
{
    if (!BossHPbarImage) return;

    // HP 비율 계산
    float HPPercent = FMath::Clamp(CurHP / MaxHP, 0.0f, 1.0f);

    // 현재 이미지의 원래 크기 가져오기
    FVector2D OriginalSize = BossHPbarImage->Brush.GetImageSize();

    // 새로운 크기 적용 (Width만 HP 비율 적용)
    FVector2D NewSize(OriginalSize.X * HPPercent, OriginalSize.Y);
    BossHPbarImage->SetRenderScale(FVector2D(HPPercent, 1.0f));

    // 또는 직접 크기 변경
    // BossHPbarImage->SetDesiredSizeInViewport(NewSize);
}

void UInGameWidget::SetBossHPVisible()
{
	BossHPbarImage->SetVisibility(ESlateVisibility::Visible);
	BossHPbarBackImage->SetVisibility(ESlateVisibility::Visible);
}

void UInGameWidget::SetBossHPHidden()
{
    BossHPbarImage->SetVisibility(ESlateVisibility::Hidden);
    BossHPbarBackImage->SetVisibility(ESlateVisibility::Hidden);
}

void UInGameWidget::VariableSetting()
{
    SetBossHPHidden();
}