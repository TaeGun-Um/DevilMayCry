// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleHUD.h"
#include "Blueprint/UserWidget.h"
#include "DevilMayCry/UI/BasicWidget/BlackBGWidget.h"
#include "DevilMayCry/UI/TitleWidget/TitleLogoWidget.h"
#include "DevilMayCry/UI/TitleWidget/TitleWidget.h"
#include "DevilMayCry/UI/TitleWidget/TestWidget.h"
#include "Kismet/GameplayStatics.h"

ATitleHUD::ATitleHUD()
{
    //static ConstructorHelpers::FClassFinder<UUserWidget> BGBlackWidgetClassFinder(TEXT("/Game/UI/Basic/WBP_BlackBGWidget"));
    //if (BGBlackWidgetClassFinder.Succeeded())
    //{
    //    BGBlackWidgetClass = BGBlackWidgetClassFinder.Class;
    //}

    //static ConstructorHelpers::FClassFinder<UUserWidget> TitleLogoWidgetClassFinder(TEXT("/Game/UI/Title/WBP_TitleLogoWidget"));
    //if (TitleLogoWidgetClassFinder.Succeeded())
    //{
    //    TitleLogoWidgetClass = TitleLogoWidgetClassFinder.Class;
    //}

    //static ConstructorHelpers::FClassFinder<UUserWidget> TitleWidgetClassFinder(TEXT("/Game/UI/Title/WBP_TitleWidget"));
    //if (TitleWidgetClassFinder.Succeeded())
    //{
    //    TitleWidgetClass = TitleWidgetClassFinder.Class;
    //}

    static ConstructorHelpers::FClassFinder<UUserWidget> TestWidgetClassFinder(TEXT("/Game/UI/Title/WBP_TestWidget"));
    if (TestWidgetClassFinder.Succeeded())
    {
        TestWidgetClass = TestWidgetClassFinder.Class;
    }
        
    EKeys::GetAllKeys(AllKeys);
}

void ATitleHUD::BeginPlay()
{
    Super::BeginPlay();

    HUDPlayerController = GetOwningPlayerController();
    //TitleWidgetInstance = CreateWidget<UTitleWidget>(GetWorld(), TitleWidgetClass);
    //if (TitleWidgetClass)
    //{
    //    TitleWidgetInstance->AddToViewport();
    //    if (HUDPlayerController)
    //    {
    //        HUDPlayerController->SetShowMouseCursor(true);

    //        //FInputModeUIOnly InputMode;
    //        //InputMode.SetWidgetToFocus(TitleWidgetInstance->TakeWidget());
    //        //HUDPlayerController->SetInputMode(InputMode);

    //        FInputModeGameAndUI InputMode;
    //        InputMode.SetWidgetToFocus(TitleWidgetInstance->TakeWidget());
    //        InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
    //        HUDPlayerController->SetInputMode(InputMode);
    //        HUDPlayerController->SetShowMouseCursor(true);
    //    }
    //}

    //BGBlackWidgetInstance = CreateWidget<UBlackBGWidget>(GetWorld(), BGBlackWidgetClass);
    //if (BGBlackWidgetClass)
    //{
    //    BGBlackWidgetInstance->AddToViewport();
    //}

    //TitleLogoWidgetInstance = CreateWidget<UTitleLogoWidget>(GetWorld(), TitleLogoWidgetClass);
    //if (TitleLogoWidgetClass)
    //{
    //    TitleLogoWidgetInstance->AddToViewport();
    //    TitleLogoWidgetInstance->PlayAnim();
    //}

    TestWidgetInstance = CreateWidget<UTestWidget>(GetWorld(), TestWidgetClass);
    if (TestWidgetInstance)
    {
        TestWidgetInstance->AddToViewport();
    }
}

void ATitleHUD::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    //if (false == bIsTitleLogoHandled && TitleLogoWidgetInstance->IsAnimationEnd())
    //{
    //    bIsTitleLogoHandled = true;
    //    TitleLogoWidgetInstance->SetVisibility(ESlateVisibility::Hidden);
    //    GetWorldTimerManager().SetTimer(
    //        TitleLogoAnimEndHandle,
    //        this,
    //        &ATitleHUD::OnTitleLogoAnimEndDelay,
    //        1.0f,
    //        false
    //    );
    //}

    //if (false == bIsTitleBackHandled && BGBlackWidgetInstance->IsAnimationEnd())
    //{
    //    bIsTitleBackHandled = true;
    //    BGBlackWidgetInstance->SetVisibility(ESlateVisibility::Hidden);
    //    TitleWidgetInstance->PlayAnim();
    //}

    //if (false == bIsTitleMenuHandled && true == bIsTitleLogoHandled && true == bIsTitleBackHandled)
    //{
    //    for (const FKey& Key : AllKeys)
    //    {
    //        if (HUDPlayerController->WasInputKeyJustPressed(Key))
    //        {
    //            bIsTitleMenuHandled = true;
    //            TitleWidgetInstance->StopBlinkAnimation();
    //            break;
    //        }
    //    }
    //}


}

void ATitleHUD::OnTitleLogoAnimEndDelay()
{
    BGBlackWidgetInstance->PlayAnim();
}
