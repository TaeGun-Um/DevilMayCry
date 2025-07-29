// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "LoadingHUD.generated.h"

/**
 * 
 */
UCLASS()
class DEVILMAYCRY_API ALoadingHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	ALoadingHUD();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	void ClassSetting();
	void VariableSetting();
	void ChangeScene();

	FTimerHandle LoadingHandle;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<class UUserWidget> BGBlackWidgetClass;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<class UUserWidget> LoadingWidgetClass;

	UPROPERTY()
	TObjectPtr<class UBlackBGWidget> BGBlackWidgetInstance;

	UPROPERTY()
	TObjectPtr<class ULoadingWidget> LoadingWidgetInstance;

	UPROPERTY()
	TObjectPtr<class APlayerController> HUDPlayerController;
};
