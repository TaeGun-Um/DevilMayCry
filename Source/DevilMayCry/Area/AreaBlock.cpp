// Fill out your copyright notice in the Description page of Project Settings.


#include "AreaBlock.h"
#include "Components/StaticMeshComponent.h"

AAreaBlock::AAreaBlock()
{
	Tags.Add(TEXT("AREA"));


	TObjectPtr<UStaticMesh> SKM = LoadObject<UStaticMesh>(nullptr, TEXT("/Script/Engine.StaticMesh'/Game/Asset/Map/Location2/Object/sm7001_seal_02/SM_AreaBlock.SM_AreaBlock'"));

	if (SKM)
	{
		GetStaticMeshComponent()->SetStaticMesh(SKM);
	}
}
