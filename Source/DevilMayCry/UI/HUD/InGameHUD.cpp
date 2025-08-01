// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameHUD.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "DevilMayCry/UI/InGameWidget/InGameWidget.h"
#include "DevilMayCry/UI/BasicWidget/BlackBGWidget.h"
#include "DevilMayCry/System/MyGameInstance.h"
#include "DevilMayCry/Character/Enemy/EnemyBase.h"
#include "EngineUtils.h"   // TActorIterator 사용 시 필요

AInGameHUD::AInGameHUD()
{
    ClassSetting();
}

void AInGameHUD::BeginPlay()
{
    Super::BeginPlay();
    VariableSetting();

    APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    if (PC)
    {
        PC->SetShowMouseCursor(false);
        FInputModeGameOnly InputMode;
        PC->SetInputMode(InputMode);
    }
}

void AInGameHUD::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    
    if (!bLoggedOnce)
    {
        ++Count;
        if (Count > 10)
        {
            bLoggedOnce = true;
        }

        UWorld* World = GetWorld();
        if (World)
        {
            APlayerController* PC = UGameplayStatics::GetPlayerController(World, 0);
            if (PC)
            {
                FString PCName = PC->GetClass()->GetName();
                UE_LOG(LogTemp, Warning, TEXT("PlayerController Class: %s"), *PCName);
            }

            AGameModeBase* GameMode = UGameplayStatics::GetGameMode(World);
            if (GameMode)
            {
                FString GMName = GameMode->GetClass()->GetName();
                UE_LOG(LogTemp, Warning, TEXT("GameMode Class: %s"), *GMName);
            }
        }
    }

    // ? Boss HP 업데이트
    if (InGameWidgetInstance)
    {
        // 월드에서 보스(EnemyBase) 액터 탐색
        for (TActorIterator<AEnemyBase> It(GetWorld()); It; ++It)
        {
            AEnemyBase* Boss = *It;
            if (Boss && !Boss->GetIsDestroy())  // 유효하고 파괴되지 않은 보스
            {
                float CurHP = Boss->GetEnermyCurHP();
                float MaxHP = Boss->GetEnermyMaxHP();

                InGameWidgetInstance->UpdateBossHPBar(CurHP, MaxHP);
                break; // 보스 하나만 업데이트
            }
        }
    }
}

void AInGameHUD::CaptureScreenshot()
{
    FScreenshotRequest::RequestScreenshot(TEXT("EndingScreen.png"), false, false);
}

void AInGameHUD::ClassSetting()
{
    //static ConstructorHelpers::FClassFinder<UUserWidget> BGBlackWidgetClassFinder(TEXT("/Game/UI/Basic/WBP_BlackBGWidget"));
    //if (BGBlackWidgetClassFinder.Succeeded())
    //{
    //    BGBlackWidgetClass = BGBlackWidgetClassFinder.Class;
    //}

    static ConstructorHelpers::FClassFinder<UUserWidget> InGameWidgetClassFinder(TEXT("/Game/UI/InGame/WBP_InGameWidget"));
    if (InGameWidgetClassFinder.Succeeded())
    {
        InGameWidgetClass = InGameWidgetClassFinder.Class;
    }


}

void AInGameHUD::VariableSetting()
{
    //// 순서대로 Create해야 Widget이 위에 덮어 씌워짐
    //BGBlackWidgetInstance = CreateWidget<UBlackBGWidget>(GetWorld(), BGBlackWidgetClass);
    //BGBlackWidgetInstance->AddToViewport();

    InGameWidgetInstance = CreateWidget<UInGameWidget>(GetWorld(), InGameWidgetClass);
    InGameWidgetInstance->AddToViewport();

    UWorld* World = GetWorld();
    UGameInstance* GIBase = World->GetGameInstance();
    UMyGameInstance* GI = Cast<UMyGameInstance>(GIBase);
    EMapChangeValue Value = GI->GetMapChangeValue();
    if (Value == EMapChangeValue::LOCATION11)
    {
        InGameWidgetInstance->SetBossHPVisible();
    }
}


