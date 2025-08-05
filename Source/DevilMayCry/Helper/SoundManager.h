// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SoundManager.generated.h"

/**
 * 
 */
UCLASS()
class DEVILMAYCRY_API USoundManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
    UFUNCTION(BlueprintCallable) // BGM 재생
    void PlayBGM(USoundBase* _NewBGM, float _Volume = 1.0f, float _StartTime = 0.0f, bool _bLoop = false);
    
    UFUNCTION(BlueprintCallable) // 효과음 재생 (UI 등)
    void PlaySFX(USoundBase* _SFX, float _Volume = 1.0f);
    
    UFUNCTION(BlueprintCallable) // BGM 정지
    void StopBGM(float _FadeOutTime = 1.0f);

    // 사운드 Getter
    FORCEINLINE TObjectPtr<class USoundBase> GetButtonSound() const { return ButtonSound; }
    FORCEINLINE TObjectPtr<class USoundBase> GetButtonSound2() const { return ButtonSound2; }
    FORCEINLINE TObjectPtr<class USoundBase> GetSelectSound() const { return SelectSound; }
    FORCEINLINE TObjectPtr<class USoundBase> GetStartSound() const { return StartSound; }
    FORCEINLINE TObjectPtr<class USoundBase> GetWindowSound() const { return WindowSound; }
    FORCEINLINE TObjectPtr<class USoundBase> GetReadySound() const { return ReadySound; }

    FORCEINLINE TObjectPtr<class USoundBase> GetTitleBGM() const { return TitleBGM; }
    FORCEINLINE TObjectPtr<class USoundBase> GetSelectBGM() const { return SelectBGM; }

    UFUNCTION(BlueprintCallable) // BGM 정지
    FORCEINLINE USoundBase* GetBossBGM() const { return BossBGM; }

protected:
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;

private:
    UPROPERTY(EditAnywhere, Category = "Sound")
    TObjectPtr<class UAudioComponent> BGMComponent;
    
    UPROPERTY(EditAnywhere, Category = "Sound")
    TObjectPtr<class USoundBase> TitleBGM;

    UPROPERTY(EditAnywhere, Category = "Sound")
    TObjectPtr<class USoundBase> SelectBGM;

    UPROPERTY(EditAnywhere, Category = "Sound")
    USoundBase* BossBGM;

    UPROPERTY(EditAnywhere, Category = "Sound")
    TObjectPtr<class USoundBase> ButtonSound;

    UPROPERTY(EditAnywhere, Category = "Sound")
    TObjectPtr<class USoundBase> ButtonSound2;

    UPROPERTY(EditAnywhere, Category = "Sound")
    TObjectPtr<class USoundBase> SelectSound;

    UPROPERTY(EditAnywhere, Category = "Sound")
    TObjectPtr<class USoundBase> StartSound;

    UPROPERTY(EditAnywhere, Category = "Sound")
    TObjectPtr<class USoundBase> WindowSound;

    UPROPERTY(EditAnywhere, Category = "Sound")
    TObjectPtr<class USoundBase> ReadySound;
};
