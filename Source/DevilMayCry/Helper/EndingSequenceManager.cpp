// Fill out your copyright notice in the Description page of Project Settings.


#include "EndingSequenceManager.h"
#include "Engine/TextureRenderTarget2D.h"
#include "DevilMayCry/System/MyGameInstance.h"

// Sets default values
AEndingSequenceManager::AEndingSequenceManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEndingSequenceManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEndingSequenceManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEndingSequenceManager::CaptureAndStoreTexture()
{
    UTexture2D* CapturedTex = ConvertRenderTargetToTexture(RenderTarget);
    if (CapturedTex)
    {
        if (UMyGameInstance* GI = Cast<UMyGameInstance>(GetGameInstance()))
        {
            GI->CapturedEndingTexture = CapturedTex;
        }
    }
}

// Helper Function
TObjectPtr<class UTexture2D> AEndingSequenceManager::ConvertRenderTargetToTexture(TObjectPtr<UTextureRenderTarget2D> _RenderTarget)
{
    if (!_RenderTarget) return nullptr;

    FTextureRenderTargetResource* Resource = _RenderTarget->GameThread_GetRenderTargetResource();

    // 픽셀 데이터를 복사
    TArray<FColor> OutBMP;
    Resource->ReadPixels(OutBMP);

    int32 Width = _RenderTarget->SizeX;
    int32 Height = _RenderTarget->SizeY;

    // 새 텍스처 생성
    UTexture2D* NewTexture = UTexture2D::CreateTransient(Width, Height);
    void* TextureData = NewTexture->GetPlatformData()->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
    FMemory::Memcpy(TextureData, OutBMP.GetData(), OutBMP.Num() * sizeof(FColor));
    NewTexture->GetPlatformData()->Mips[0].BulkData.Unlock();

    NewTexture->UpdateResource();
    return NewTexture;
}