// Fill out your copyright notice in the Description page of Project Settings.


#include "BGBlackWidget.h"

bool UBGBlackWidget::Initialize()
{
    Super::Initialize();
    
    return true;
}

void UBGBlackWidget::AnimInit()
{
    IUIAnimationInterface::AnimInit();
    AnimFinishEvent.BindDynamic(this, &UBGBlackWidget::AnimFinishedCall);
    if (FadeAnimation)
    {
        BindToAnimationFinished(FadeAnimation, AnimFinishEvent);
    }
}

void UBGBlackWidget::PlayAnim()
{
    PlayAnimation(FadeAnimation);
}

void UBGBlackWidget::AnimFinishedCall()
{
    IUIAnimationInterface::SetAnimFinished();
}