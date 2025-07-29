// Fill out your copyright notice in the Description page of Project Settings.


#include "LoadingHUD.h"
#include "DevilMayCry/UI/LoadingWidget/LoadingWidget.h"
#include "DevilMayCry/UI/BasicWidget/BlackBGWidget.h"
#include "Kismet/GameplayStatics.h"

ALoadingHUD::ALoadingHUD()
{
    ClassSetting();
}

void ALoadingHUD::BeginPlay()
{
    Super::BeginPlay();
    VariableSetting();

    GetWorldTimerManager().SetTimer(LoadingHandle, this, &ALoadingHUD::ChangeScene, 3.0f, false);
    // CreateFSM();
}

void ALoadingHUD::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

void ALoadingHUD::ChangeScene()
{
    UWorld* World = GetWorld();
    if (!World)
    {
        return;
    }

    ENetMode NetMode = World->GetNetMode();

    if (NetMode == NM_Standalone)
    {
        UGameplayStatics::OpenLevel(this, FName(TEXT("/Game/Scene/Location2")));
    }
    else if (NetMode == NM_ListenServer)
    {
        World->ServerTravel("/Game/Scene/Location2?listen");
    }
    else if (NetMode == NM_Client)
    {
        UE_LOG(LogTemp, Log, TEXT("Client does not control level travel"));
    }
}

void ALoadingHUD::ClassSetting()
{
    static ConstructorHelpers::FClassFinder<UUserWidget> LoadingWidgetClassFinder(TEXT("/Game/UI/Loading/WBP_LoadingWidget"));
    if (LoadingWidgetClassFinder.Succeeded())
    {
        LoadingWidgetClass = LoadingWidgetClassFinder.Class;
    }

    static ConstructorHelpers::FClassFinder<UUserWidget> BGBlackWidgetClassFinder(TEXT("/Game/UI/Basic/WBP_BlackBGWidget"));
    if (BGBlackWidgetClassFinder.Succeeded())
    {
        BGBlackWidgetClass = BGBlackWidgetClassFinder.Class;
    }
}

void ALoadingHUD::VariableSetting()
{
    HUDPlayerController = GetOwningPlayerController();

    // ¼ø¼­´ë·Î CreateÇØ¾ß WidgetÀÌ À§¿¡ µ¤¾î ¾º¿öÁü
    BGBlackWidgetInstance = CreateWidget<UBlackBGWidget>(GetWorld(), BGBlackWidgetClass);
    BGBlackWidgetInstance->AddToViewport();

    LoadingWidgetInstance = CreateWidget<ULoadingWidget>(GetWorld(), LoadingWidgetClass);
    LoadingWidgetInstance->AddToViewport();
    LoadingWidgetInstance->PlayFadeAnimation();
    LoadingWidgetInstance->PlayArrowAnimation();
    // LoadingWidgetInstance->SetVisibility(ESlateVisibility::Hidden);

    if (HUDPlayerController)
    {
        HUDPlayerController->SetShowMouseCursor(true);

        FInputModeGameAndUI InputMode;
        InputMode.SetWidgetToFocus(LoadingWidgetInstance->TakeWidget());
        InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
        HUDPlayerController->SetInputMode(InputMode);
        HUDPlayerController->SetShowMouseCursor(true);
    }
}