// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleLogoWidget.h"
#include "DevilMayCry/UI/BasicWidget/AnimationWidget.h"

bool UTitleLogoWidget::Initialize()
{
	Super::Initialize();
	VariableSetting();

	return true;
}

void UTitleLogoWidget::VariableSetting()
{
	AnimationEndEvent.BindDynamic(this, &UTitleLogoWidget::SetAnimationEnd);
	if (FadeAnimation)
	{
		BindToAnimationFinished(FadeAnimation, AnimationEndEvent);
	}
}