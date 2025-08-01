// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InGameWidget.generated.h"

/**
 * 
 */
UCLASS()
class DEVILMAYCRY_API UInGameWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetBossHPVisible();
	void SetBossHPHidden();
	void UpdateBossHPBar(float _CurHP, float _MaxHP);

protected:
	virtual bool Initialize() override;

private:
	void VariableSetting();

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UImage> HPbarBackImage;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UImage> HPbarImage;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UImage> BossHPbarBackImage;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UImage> BossHPbarImage;
};
