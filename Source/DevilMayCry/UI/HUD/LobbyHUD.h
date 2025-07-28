// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "DevilMayCry/UI/Interface/FSM.h"
#include "LobbyHUD.generated.h"

UENUM(BlueprintType)
enum class EMultiFSMState : uint8
{
	DISCONECT,
	MULTIPLAY,
	NONE
};

/**
 * 
 */
UCLASS()
class DEVILMAYCRY_API ALobbyHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	ALobbyHUD();
	void RefreshPlayerStates();

	// Getter, Setter
	void SetHostIP(FString _Text) { HostIP = _Text; }

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	void ClassSetting();
	void VariableSetting();
	void CreateFSM();

	EMultiFSMState State;
	TArray<FKey> AllKeys;

	UPROPERTY()
	TObjectPtr<class UFSM> MultiFSM;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<class UUserWidget> BGBlackWidgetClass;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<class UUserWidget> MultiPlayWidgetClass;

	UPROPERTY()
	TObjectPtr<class UBlackBGWidget> BGBlackWidgetInstance;

	UPROPERTY()
	TObjectPtr<class USelectMultiplayWidget> MultiPlayWidgetInstance;

	UPROPERTY()
	TObjectPtr<class APlayerController> LobbyPlayerController;

	FString HostIP = TEXT("");
};
