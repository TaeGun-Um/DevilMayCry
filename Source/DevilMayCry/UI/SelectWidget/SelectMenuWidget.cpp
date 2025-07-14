// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectMenuWidget.h"

bool USelectMenuWidget::Initialize()
{
	if (false == Super::Initialize())
	{
		return false;
	}
	 
	return true;
}

void USelectMenuWidget::PlayFadeAnimation()
{
	PlayAnimation(FadeAnimation);
}