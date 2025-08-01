// Fill out your copyright notice in the Description page of Project Settings.


#include "AreaPortal.h"
#include "Components/BoxComponent.h"
#include "../Character/Player/ParentCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "DevilMayCry/System/MyGameInstance.h"
#include "DevilMayCry/System/InGameModeBase.h"

AAreaPortal::AAreaPortal()
{
    if (UBoxComponent* Box = Cast<UBoxComponent>(GetCollisionComponent()))
    {
        RootComponent = Box;
        Box->OnComponentBeginOverlap.AddDynamic(this, &AAreaPortal::OverlapBegin);
        Box->SetBoxExtent(FVector(200.f, 200.f, 200.f));
    }

    Tags.Add(TEXT("PORTAL"));
}

void AAreaPortal::OverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != nullptr)
	{
		if (TObjectPtr<AParentCharacter> Player = Cast<AParentCharacter>(OtherActor))
		{
            if (HasAuthority()) // Server
            {
                UWorld* World = GetWorld();
                if (!World) return;

                UMyGameInstance* GI = Cast<UMyGameInstance>(World->GetGameInstance());
                if (GI)
                {
                    GI->SetMapChangeValue(EMapChangeValue::LOCATION11);
                }

                // 서버가 전체 클라이언트 포함 레벨 이동
                World->ServerTravel(TEXT("/Game/Scene/LoadingScene?listen"));
            }
		}
	}
}

//void AAreaPortal::OverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
//{
//    if (OtherActor != nullptr)
//    {
//        if (TObjectPtr<AParentCharacter> Player = Cast<AParentCharacter>(OtherActor))
//        {
//            if (HasAuthority()) // 서버에서만 실행
//            {
//                UWorld* World = GetWorld();
//                if (!World) return;
//
//                // GameMode 가져오기 및 캐스팅
//                AInGameModeBase* GM = Cast<AInGameModeBase>(World->GetAuthGameMode());
//                if (GM)
//                {
//                    GM->EndingStart(); // EndingStart() 호출
//                }
//        }
//    }
//}