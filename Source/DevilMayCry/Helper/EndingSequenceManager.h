// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EndingSequenceManager.generated.h"

UCLASS()
class DEVILMAYCRY_API AEndingSequenceManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEndingSequenceManager();
	void CaptureAndStoreTexture();
	TObjectPtr<class UTexture2D> ConvertRenderTargetToTexture(TObjectPtr<UTextureRenderTarget2D> _RenderTarget);

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "Ending")
	TObjectPtr<class UTextureRenderTarget2D> RenderTarget;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class USceneCaptureComponent2D> SceneCapture;
};
