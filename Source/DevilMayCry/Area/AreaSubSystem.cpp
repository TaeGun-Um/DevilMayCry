// Fill out your copyright notice in the Description page of Project Settings.


#include "AreaSubSystem.h"
#include "Engine/TriggerBase.h"
#include "Engine/StaticMeshActor.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "Engine/OverlapResult.h"
#include "Util\IteratorUtil.h"
#include "Components/ShapeComponent.h"
#include "Components/SphereComponent.h"

#include "../Character/Enemy/EnemyBase.h"
#include "AreaBlockingVolume.h"
#include "AreaTrigger.h"



UAreaSubSystem::UAreaSubSystem()
{
}

void UAreaSubSystem::FindPhase(UWorld* World)
{
	TArray<AActor*> TriggerActors;

	for (int32 i = 0; i < static_cast<int32>(EPhase::MAX); i++)
	{
		FString Name = StaticEnum<EPhase>()->GetNameStringByIndex(i);

		//Phase 태그를 단놈 찾기
		UGameplayStatics::GetAllActorsOfClassWithTag(World, ATriggerBase::StaticClass(), FName(Name), TriggerActors);

		//어차피 태그 똑같은거 한놈만 나올거라 별의미 없긴함
		for (auto TriggerIter : TriggerActors)
		{
			auto Iter = Cast< ATriggerBase>(TriggerIter);
			auto SphereComp = Cast<USphereComponent>(Iter->GetCollisionComponent());


			TArray<FOverlapResult> Overlaps;
			FCollisionShape Sphere = FCollisionShape::MakeSphere(SphereComp->GetScaledSphereRadius());

			// Overlap된 액터 체크
			World->OverlapMultiByObjectType(Overlaps, Iter->GetActorLocation(), FQuat::Identity,
				FCollisionObjectQueryParams::AllObjects, Sphere);

			for (auto& OverlapAreaActor : Overlaps)
			{
				auto AreaActor = OverlapAreaActor.GetActor();

				//AREA 태그 단놈만 가져와서 분류
				if (AreaActor->ActorHasTag(TEXT("AREA")))
				{
					if (AreaActor->GetClass() == AAreaTrigger::StaticClass())
					{
						PhaseArray[i].Trigger = Cast<AAreaTrigger>(AreaActor);
					}
					else if (AreaActor->GetClass() == AAreaBlockingVolume::StaticClass())
					{
						PhaseArray[i].BlockArray.Add(Cast<AAreaBlockingVolume>(AreaActor));
						
						AreaActor->SetActorHiddenInGame(true);
						AreaActor->SetActorEnableCollision(false);
						AreaActor->SetActorTickEnabled(false);
					}
					else if (AreaActor->GetClass() == AStaticMeshActor::StaticClass())
					{
						PhaseArray[i].MeshArray.Add(Cast<AStaticMeshActor>(AreaActor));

						AreaActor->SetActorHiddenInGame(true);
						AreaActor->SetActorEnableCollision(false);
						AreaActor->SetActorTickEnabled(false);
					}
					else if (Cast<AEnemyBase>(AreaActor))
					{
						bool IsFirst = false;
						PhaseArray[i].EnemyArray.Add(Cast<AEnemyBase>(AreaActor), &IsFirst);

						//중복검출이 되는 문제때문에 중복체크
						if (!IsFirst)
						{
							AreaActor->SetActorHiddenInGame(true);
							AreaActor->SetActorEnableCollision(false);
							AreaActor->SetActorTickEnabled(false);

							AreaActor->OnDestroyed.AddDynamic(this, &UAreaSubSystem::OnDestroyCheck);
						}						
					}
					else
					{
						//위에가 다 아니었으면 로케이션 세터일거임
						PhaseArray[i].Location = AreaActor;
					}
				}
			}
		}
	}
}

void UAreaSubSystem::OnDestroyCheck(AActor* DestroyActor)
{
	++PhaseArray[CurPhase].DeathCount;
	UE_LOG(LogTemp, Warning, TEXT("Dest"));
	UE_LOG(LogTemp, Warning, TEXT("Count %d"), PhaseArray[CurPhase].DeathCount);

	if (PhaseArray[CurPhase].DeathCount == PhaseArray[CurPhase].EnemyArray.Num())
	{
		UE_LOG(LogTemp, Warning, TEXT("End"));
		SwitchPhase(false);
	}
}

void UAreaSubSystem::SwitchPhase(bool Value)
{

	if (Value)
	{
		if (CurPhase < static_cast<int32>(EPhase::MAX))
		{
			++CurPhase;
		}

		//모든 플레이어 가져와서 위치 변경
		for (auto Iter = GetWorld()->GetPlayerControllerIterator(); Iter; ++Iter)
		{
			if (Iter->Get())
			{
				AActor* Char = Cast<AActor>(Iter->Get()->GetPawn());
				Char->SetActorLocation(PhaseArray[CurPhase].Location->GetActorLocation());
			}
		}

		for (auto Iter : PhaseArray[CurPhase].EnemyArray)
		{
			Iter->SetActorHiddenInGame(!Value);
			Iter->SetActorEnableCollision(Value);
			Iter->SetActorTickEnabled(Value);
		}
	}

		for (auto Iter : PhaseArray[CurPhase].MeshArray)
		{
			Iter->SetActorHiddenInGame(!Value);
			Iter->SetActorEnableCollision(Value);
			Iter->SetActorTickEnabled(Value);
		}

		for (auto Iter : PhaseArray[CurPhase].BlockArray)
		{
			Iter->SetActorHiddenInGame(!Value);
			Iter->SetActorEnableCollision(Value);
			Iter->SetActorTickEnabled(Value);
		}
	
}

void UAreaSubSystem::OnWorldBeginPlay(UWorld& InWorld)
{
	FString LevelName = UGameplayStatics::GetCurrentLevelName(&InWorld);

	//특정 레벨일때만 체크
	if (LevelName == TEXT("Location2"))
	{
		PhaseArray.SetNum(static_cast<uint8>(EPhase::MAX));

		FindPhase(&InWorld);
	}
}