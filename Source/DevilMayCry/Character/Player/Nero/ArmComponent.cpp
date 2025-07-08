// Fill out your copyright notice in the Description page of Project Settings.


#include "ArmComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "../ParentCharacter.h"

// Sets default values for this component's properties
UArmComponent::UArmComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	SkmComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkmComp"));

	arrDevilBreaker.SetNum(static_cast<int>(EArmType::MAX));

	TObjectPtr<USkeletalMesh> Overture = LoadObject<USkeletalMesh>(nullptr, TEXT("/Script/Engine.SkeletalMesh'/Game/Asset/UI/UIMesh/NeroItemMesh/NeroArm/Overture/OvertureArmUI.OvertureArmUI'"));

	if (Overture)
	{
		arrDevilBreaker[static_cast<int>(EArmType::OVERTURE)] = Overture;
		UE_LOG(LogTemp, Warning, TEXT("Overture Load Success"));
	}

	TObjectPtr<USkeletalMesh> Gerbera = LoadObject<USkeletalMesh>(nullptr, TEXT("/Script/Engine.SkeletalMesh'/Game/Asset/UI/UIMesh/NeroItemMesh/NeroArm/Gerbera/GerberaArmUI.GerberaArmUI'"));

	if (Gerbera)
	{
		arrDevilBreaker[static_cast<int>(EArmType::GERBERA)] = Gerbera;
		UE_LOG(LogTemp, Warning, TEXT("Gerbera Load Success"));
	}
	
	/*TObjectPtr<USkeletalMesh> Buster = LoadObject<USkeletalMesh>(nullptr, TEXT("/Script/Engine.SkeletalMesh'/Game/Asset/UI/UIMesh/NeroItemMesh/NeroArm/Buster_Arm/BusterArmUI.BusterArmUI'"));

	if (Buster)
	{
		arrDevilBreaker[static_cast<int>(EArmType::BUSTER)] = Buster;
		UE_LOG(LogTemp, Warning, TEXT("Buster Load Success"));
	}*/
}

void UArmComponent::ChangeNextArm()
{
	uint8 TempType = static_cast<int>(CurArmType);

	if (++TempType == static_cast<int>(EArmType::MAX))
	{
		CurArmType = static_cast<EArmType>(0);
	}
	else
	{
		CurArmType = static_cast<EArmType>(TempType);
	}

	SkmComp->SetSkeletalMesh(arrDevilBreaker[static_cast<int>(CurArmType)]);
	SkmComp->SetLeaderPoseComponent(Owner->GetMesh());
}



// Called when the game starts
void UArmComponent::BeginPlay()
{
	Super::BeginPlay();

	Owner = Cast<AParentCharacter>(GetOwner());

	SkmComp->AttachToComponent(Owner->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform);
	SkmComp->SetLeaderPoseComponent(Owner->GetMesh());
	
	SkmComp->SetSkeletalMesh(arrDevilBreaker[static_cast<int>(CurArmType)]); 	
}


// Called every frame
void UArmComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

