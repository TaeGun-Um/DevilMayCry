// Fill out your copyright notice in the Description page of Project Settings.


#include "AreaTrigger.h"
#include "Components/SphereComponent.h"
#include "../Character/Player/ParentCharacter.h"
#include "AreaSubSystem.h"

AAreaTrigger::AAreaTrigger()
{
	TObjectPtr <USphereComponent> Sphere = Cast<USphereComponent>(GetCollisionComponent());
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AAreaTrigger::OverlapBegin);
	Sphere->SetSphereRadius(300.f);

	Tags.Add(TEXT("AREA"));
}

void AAreaTrigger::OverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor!= nullptr)
	{
		TObjectPtr<AParentCharacter> Player = Cast<AParentCharacter>(OtherActor);

		//플레이어 였으면 페이즈 시작해주고 삭제
		if (Player != nullptr)
		{
			Cast<UAreaSubSystem>(GetWorld()->GetSubsystemBase(UAreaSubSystem::StaticClass()))->SwitchPhase(true);;
		}

		Destroy();
	}
}
