// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleLogoWidget.h"

bool UTitleLogoWidget::Initialize()
{
    Super::Initialize();

    return true;
}

void UTitleLogoWidget::AnimInit()
{
    IUIAnimationInterface::AnimInit();
    AnimFinishEvent.BindDynamic(this, &UTitleLogoWidget::AnimFinishedCall);
    if (FadeAnimation)
    {
        BindToAnimationFinished(FadeAnimation, AnimFinishEvent);
    }
}

void UTitleLogoWidget::PlayAnim()
{
    PlayAnimation(FadeAnimation);
}

void UTitleLogoWidget::AnimFinishedCall()
{
    IUIAnimationInterface::SetAnimFinished();
}