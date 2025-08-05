// Fill out your copyright notice in the Description page of Project Settings.


#include "SoundManager.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"

void USoundManager::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);

    ButtonSound = LoadObject<USoundBase>(nullptr, TEXT("/Game/Asset/Sound/UISound/ButtonSound2.ButtonSound2"));
    ButtonSound2 = LoadObject<USoundBase>(nullptr, TEXT("/Game/Asset/Sound/UISound/ButtonSound.ButtonSound"));
    SelectSound = LoadObject<USoundBase>(nullptr, TEXT("/Game/Asset/Sound/UISound/UIButtonSelectSound.UIButtonSelectSound"));
    StartSound = LoadObject<USoundBase>(nullptr, TEXT("/Game/Asset/Sound/UISound/StartButtonSelect.StartButtonSelect"));
    WindowSound = LoadObject<USoundBase>(nullptr, TEXT("/Game/Asset/Sound/UISound/UIESCSound.UIESCSound"));
    ReadySound = LoadObject<USoundBase>(nullptr, TEXT("/Game/Asset/Sound/UISound/DevilBreakerUISound.DevilBreakerUISound"));

    TitleBGM = LoadObject<USoundBase>(nullptr, TEXT("/Game/Asset/Sound/BGM/Titlescreen.Titlescreen"));
    SelectBGM = LoadObject<USoundBase>(nullptr, TEXT("/Game/Asset/Sound/BGM/Ugh_Come_On.Ugh_Come_On"));
    // SelectSound = LoadObject<USoundBase>(nullptr, TEXT("/Game/Asset/Sound/BGM/TitleBGM.TitleBGM"));

    // UE_LOG(LogTemp, Log, TEXT("[SoundManager] 사운드 에셋 로드 완료"));
}

void USoundManager::PlayBGM(USoundBase* _NewBGM, float _Volume, float _StartTime, bool _bLoop)
{
    if (!_NewBGM) return;

    // 안전하게 BGMComponent 생성 및 등록
    if (!BGMComponent)
    {
        BGMComponent = NewObject<UAudioComponent>(GetWorld()->GetFirstPlayerController());
        BGMComponent->bIsUISound = true;
        BGMComponent->bAllowSpatialization = false;
        BGMComponent->RegisterComponent();
        BGMComponent->AttachToComponent(GetWorld()->GetFirstPlayerController()->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
    }

    // 체크
    if (BGMComponent->IsRegistered() && BGMComponent->IsPlaying() && BGMComponent->Sound == _NewBGM)
    {
        return; 
    }

    if (USoundWave* SW = Cast<USoundWave>(_NewBGM))
    {
        SW->bLooping = _bLoop; // SoundWave 루프 설정
    }
    else
    {
        BGMComponent->SetBoolParameter(FName("Looping"), _bLoop);
    }

    BGMComponent->SetSound(_NewBGM);
    BGMComponent->Play(_StartTime);
    BGMComponent->SetVolumeMultiplier(_Volume);
}

void USoundManager::StopBGM(float _FadeOutTime)
{
    if (BGMComponent && BGMComponent->IsPlaying())
    {
        BGMComponent->FadeOut(_FadeOutTime, 0.0f);
    }
}

void USoundManager::PlaySFX(USoundBase* _SFX, float _Volume)
{
    if (_SFX)
    {
        UGameplayStatics::PlaySound2D(GetWorld(), _SFX, _Volume);
    }
}