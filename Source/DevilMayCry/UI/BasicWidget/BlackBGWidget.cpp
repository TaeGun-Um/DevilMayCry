// Fill out your copyright notice in the Description page of Project Settings.


#include "BlackBGWidget.h"
#include "DevilMayCry/UI/BasicWidget/AnimationWidget.h"

bool UBlackBGWidget::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}

	AnimationEndEventSetting();

	return true;
}

void UBlackBGWidget::PlayAnim()
{
	PlayAnimation(FadeAnimation);
}

void UBlackBGWidget::AnimationEndEventSetting()
{
	Super::AnimationEndEventSetting();

	if (FadeAnimation)
	{
		BindToAnimationFinished(FadeAnimation, AnimationEndEvent);
	}
}
