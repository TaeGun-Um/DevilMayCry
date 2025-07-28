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

protected:
	virtual bool Initialize() override;

private:
	void VariableSetting();

};
