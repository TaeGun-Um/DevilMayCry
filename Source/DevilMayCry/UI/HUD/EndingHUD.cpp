// Fill out your copyright notice in the Description page of Project Settings.


#include "EndingHUD.h"
#include "DevilMayCry/UI/LoadingWidget/LoadingWidget.h"
#include "DevilMayCry/UI/EndingWidget/EndingWidget.h"
#include "DevilMayCry/UI/BasicWidget/BlackBGWidget.h"
#include "Kismet/GameplayStatics.h"
#include "DevilMayCry/System/MyGameInstance.h"

AEndingHUD::AEndingHUD()
{
    ClassSetting();
}

void AEndingHUD::BeginPlay()
{
    Super::BeginPlay();
    VariableSetting();

    HUDPlayerController = GetOwningPlayerController();
    if (HUDPlayerController)
    {
        FInputModeGameAndUI InputMode;
        InputMode.SetWidgetToFocus(EndingWidgetInstance->TakeWidget());
        InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
        HUDPlayerController->SetInputMode(InputMode);
        HUDPlayerController->SetShowMouseCursor(true);
    }

    if (UMyGameInstance* GI = Cast<UMyGameInstance>(GetGameInstance()))
    {
        if (GI->CapturedEndingTexture)
        {
             EndingWidgetInstance->SetCapturedTexture(GI->CapturedEndingTexture);
             EndingWidgetInstance->AddToViewport();
        }
    }
}

void AEndingHUD::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

void AEndingHUD::ChangeScene()
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

void AEndingHUD::ClassSetting()
{
    static ConstructorHelpers::FClassFinder<UUserWidget> EndingWidgetClassFinder(TEXT("/Game/UI/Ending/WBP_EndingWidget"));
    if (EndingWidgetClassFinder.Succeeded())
    {
        EndingWidgetClass = EndingWidgetClassFinder.Class;
    }

    //static ConstructorHelpers::FClassFinder<UUserWidget> BGBlackWidgetClassFinder(TEXT("/Game/UI/Basic/WBP_BlackBGWidget"));
    //if (BGBlackWidgetClassFinder.Succeeded())
    //{
    //    BGBlackWidgetClass = BGBlackWidgetClassFinder.Class;
    //}
}

void AEndingHUD::VariableSetting()
{
    //HUDPlayerController = GetOwningPlayerController();

    //// ¼ø¼­´ë·Î CreateÇØ¾ß WidgetÀÌ À§¿¡ µ¤¾î ¾º¿öÁü
    //BGBlackWidgetInstance = CreateWidget<UBlackBGWidget>(GetWorld(), BGBlackWidgetClass);
    //BGBlackWidgetInstance->AddToViewport();

    EndingWidgetInstance = CreateWidget<UEndingWidget>(GetWorld(), EndingWidgetClass);
    EndingWidgetInstance->AddToViewport();
}

