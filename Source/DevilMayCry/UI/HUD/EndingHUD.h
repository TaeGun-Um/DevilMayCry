// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "EndingHUD.generated.h"

/**
 * 
 */
UCLASS()
class DEVILMAYCRY_API AEndingHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	AEndingHUD();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	void ClassSetting();
	void VariableSetting();
	void ChangeScene();

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<class UUserWidget> EndingWidgetClass;

	UPROPERTY()
	TObjectPtr<class UEndingWidget> EndingWidgetInstance;

	UPROPERTY()
	TObjectPtr<class APlayerController> HUDPlayerController;
};
