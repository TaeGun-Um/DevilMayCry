// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AnimationWidget.generated.h"

/**
 * 
 */
UCLASS()
class DEVILMAYCRY_API UAnimationWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	bool IsAnimationEnd() const;

protected:
	UFUNCTION()
	void SetAnimationEnd();
	virtual void AnimationEndEventSetting();

	FWidgetAnimationDynamicEvent AnimationEndEvent;

private:
	bool bIsAnimationEnd = false;

};
