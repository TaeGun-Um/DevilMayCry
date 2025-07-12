// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimationWidget.h"

void UAnimationWidget::AnimationEndEventSetting()
{
    AnimationEndEvent.BindDynamic(this, &UAnimationWidget::SetAnimationEnd);
}

void UAnimationWidget::SetAnimationEnd()
{
	bIsAnimationEnd = true;
}

bool UAnimationWidget::IsAnimationEnd() const
{
	return bIsAnimationEnd;
}