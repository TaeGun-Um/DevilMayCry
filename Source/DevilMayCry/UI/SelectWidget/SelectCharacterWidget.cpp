// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectCharacterWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "Components/CanvasPanelSlot.h"

bool USelectCharacterWidget::Initialize()
{
    if (false == Super::Initialize())
    {
        return false;
    }

    if (NeroBackImage) // for Nero
    {
        UCanvasPanelSlot* CharacterImageSlot = Cast<UCanvasPanelSlot>(NeroBackImage->Slot);
        if (CharacterImageSlot)
        {
            CharacterImageSlot->SetAnchors(FAnchors(0.5f, 0.5f)); // Button Center Ref.
            CharacterImageSlot->SetAlignment(FVector2D(0.5f, 0.5f)); // Alignment
            CharacterImageSlot->SetPosition(FVector2D(-400.0f, 0.f));
            CharacterImageSlot->SetSize(FVector2D(450.f, 700.f));
        }

        UMaterialInterface* BaseMaterial = Cast<UMaterialInterface>(StaticLoadObject(UMaterialInterface::StaticClass(), nullptr,
            TEXT("/Game/UI/Select/MI_Graysclae_NeroBack")));
        if (BaseMaterial)
        {
            NeroBackMaterial = UMaterialInstanceDynamic::Create(BaseMaterial, this);
            NeroBackImage->SetBrushFromMaterial(NeroBackMaterial);
        }
    }

    if (VergilBackImage) // for Vergil
    {
        UCanvasPanelSlot* CharacterImageSlot = Cast<UCanvasPanelSlot>(VergilBackImage->Slot);
        if (CharacterImageSlot)
        {
            CharacterImageSlot->SetAnchors(FAnchors(0.5f, 0.5f)); // Button Center Ref.
            CharacterImageSlot->SetAlignment(FVector2D(0.5f, 0.5f)); // Alignment
            CharacterImageSlot->SetPosition(FVector2D(400.0f, 0.f));
            CharacterImageSlot->SetSize(FVector2D(450.f, 700.f));
        }

        UMaterialInterface* BaseMaterial = Cast<UMaterialInterface>(StaticLoadObject(UMaterialInterface::StaticClass(), nullptr,
            TEXT("/Game/UI/Select/MI_Graysclae_VergilBack")));
        if (BaseMaterial)
        {
            VergilBackMaterial = UMaterialInstanceDynamic::Create(BaseMaterial, this);
            VergilBackImage->SetBrushFromMaterial(VergilBackMaterial);
        }
    }

    if (NeroImage) // for Vergil
    {
        UCanvasPanelSlot* NeroImageSlot = Cast<UCanvasPanelSlot>(NeroImage->Slot);
        if (NeroImageSlot)
        {
            NeroImageSlot->SetAnchors(FAnchors(0.5f, 0.5f)); // Button Center Ref.
            NeroImageSlot->SetAlignment(FVector2D(0.5f, 0.5f)); // Alignment
            NeroImageSlot->SetPosition(FVector2D(-400.0f, 0.f));
            NeroImageSlot->SetSize(FVector2D(800.f, 800.f));
        }

        UMaterialInterface* BaseMaterial = Cast<UMaterialInterface>(StaticLoadObject(UMaterialInterface::StaticClass(), nullptr,
            TEXT("/Game/UI/Select/MI_Graysclae_Nero")));
        if (BaseMaterial)
        {
            NeroMaterial = UMaterialInstanceDynamic::Create(BaseMaterial, this);
            NeroImage->SetBrushFromMaterial(NeroMaterial);
        }
    }

    if (VergilImage) // for Vergil
    {
        UCanvasPanelSlot* VergilImageSlot = Cast<UCanvasPanelSlot>(VergilImage->Slot);
        if (VergilImageSlot)
        {
            VergilImageSlot->SetAnchors(FAnchors(0.5f, 0.5f)); // Button Center Ref.
            VergilImageSlot->SetAlignment(FVector2D(0.5f, 0.5f)); // Alignment
            VergilImageSlot->SetPosition(FVector2D(400.0f, 0.f));
            VergilImageSlot->SetSize(FVector2D(800.f, 800.f));
        }

        UMaterialInterface* BaseMaterial = Cast<UMaterialInterface>(StaticLoadObject(UMaterialInterface::StaticClass(), nullptr,
            TEXT("/Game/UI/Select/MI_Graysclae_Vergil")));
        if (BaseMaterial)
        {
            VergilMaterial = UMaterialInstanceDynamic::Create(BaseMaterial, this);
            VergilImage->SetBrushFromMaterial(VergilMaterial);
        }
    }

    if (NeroButton)
    {
        NeroButton->OnClicked.AddDynamic(this, &USelectCharacterWidget::NeroButtonClicked);
        NeroButton->OnHovered.AddDynamic(this, &USelectCharacterWidget::NeroButtonHovered);
        NeroButton->OnUnhovered.AddDynamic(this, &USelectCharacterWidget::NeroButtonUnHovered);

        UCanvasPanelSlot* NeroButtonSlot = Cast<UCanvasPanelSlot>(NeroButton->Slot);
        if (NeroButtonSlot)
        {
            NeroButtonSlot->SetAnchors(FAnchors(0.5f, 0.5f)); // Button Center Ref.
            NeroButtonSlot->SetAlignment(FVector2D(0.5f, 0.5f)); // Alignment
            NeroButtonSlot->SetPosition(FVector2D(-400.0f, 0.f));
            NeroButtonSlot->SetSize(FVector2D(450.f, 700.f));
        }
    }

    if (VergilButton)
    {
        VergilButton->OnClicked.AddDynamic(this, &USelectCharacterWidget::VergilButtonClicked);
        VergilButton->OnHovered.AddDynamic(this, &USelectCharacterWidget::VergilButtonHovered);
        VergilButton->OnUnhovered.AddDynamic(this, &USelectCharacterWidget::VergilButtonUnHovered);

        UCanvasPanelSlot* VergilButtonSlot = Cast<UCanvasPanelSlot>(VergilButton->Slot);
        if (VergilButtonSlot)
        {
            VergilButtonSlot->SetAnchors(FAnchors(0.5f, 0.5f)); // Button Center Ref.
            VergilButtonSlot->SetAlignment(FVector2D(0.5f, 0.5f)); // Alignment
            VergilButtonSlot->SetPosition(FVector2D(400.0f, 0.f));
            VergilButtonSlot->SetSize(FVector2D(450.f, 700.f));
        }
    }

    CharacterType = ECharacterType::None;

    return true;
}

void USelectCharacterWidget::NeroButtonClicked()
{
    SetIsEnd();
    SetVisibility(ESlateVisibility::Hidden);
}

void USelectCharacterWidget::NeroButtonHovered()
{
    bIsHovered = true;
    if (ECharacterType::Nero == CharacterType)
    {
        return;
    }

    if (ECharacterType::Nero != CharacterType)
    {
        if (IsAnimationPlaying(VergilSelectAnimation))
        {
            StopAnimation(VergilSelectAnimation);
        }

        UCanvasPanelSlot* CharacterImageSlot = Cast<UCanvasPanelSlot>(VergilBackImage->Slot);
        if (CharacterImageSlot)
        {
            CharacterImageSlot->SetSize(FVector2D(450.f, 700.f));
        }
        UCanvasPanelSlot* VergilImageSlot = Cast<UCanvasPanelSlot>(VergilImage->Slot);
        if (VergilImageSlot)
        {
            VergilImageSlot->SetSize(FVector2D(800.f, 800.f));
        }

        VergilMaterial->SetScalarParameterValue(FName("ColorAmount"), 0.0f);
        VergilBackMaterial->SetScalarParameterValue(FName("ColorAmount"), 0.0f);
    }

    CharacterType = ECharacterType::Nero;
    PlayAnimation(NeroSelectAnimation);
}

void USelectCharacterWidget::NeroButtonUnHovered()
{
    SetUnHovered();
}

void USelectCharacterWidget::VergilButtonClicked()
{
    SetIsEnd();
    SetVisibility(ESlateVisibility::Hidden);
}

void USelectCharacterWidget::VergilButtonHovered()
{
    bIsHovered = true;
    if (ECharacterType::Vergil == CharacterType)
    {
        return;
    }

    if (ECharacterType::Vergil != CharacterType)
    {
        if (IsAnimationPlaying(NeroSelectAnimation))
        {
            StopAnimation(NeroSelectAnimation);
        }

        UCanvasPanelSlot* CharacterImageSlot = Cast<UCanvasPanelSlot>(NeroBackImage->Slot);
        if (CharacterImageSlot)
        {
            CharacterImageSlot->SetSize(FVector2D(450.f, 700.f));
        }
        UCanvasPanelSlot* NeroImageSlot = Cast<UCanvasPanelSlot>(NeroImage->Slot);
        if (NeroImageSlot)
        {
            NeroImageSlot->SetSize(FVector2D(800.f, 800.f));
        }

        NeroMaterial->SetScalarParameterValue(FName("ColorAmount"), 0.0f);
        NeroBackMaterial->SetScalarParameterValue(FName("ColorAmount"), 0.0f);
    }

    CharacterType = ECharacterType::Vergil;
    PlayAnimation(VergilSelectAnimation);
}

void USelectCharacterWidget::VergilButtonUnHovered()
{
    SetUnHovered();
}

void USelectCharacterWidget::PlayFadeAnimation()
{
    PlayAnimation(FadeAnimation);
}

ECharacterType USelectCharacterWidget::GetCharacterType()
{
    return CharacterType;
}

void USelectCharacterWidget::SetUnHovered()
{
    bIsHovered = false;
}

bool USelectCharacterWidget::IsButtonHovered()
{
    return bIsHovered;
}

void USelectCharacterWidget::SetIsEnd()
{
    bIsEnd = true;
}

bool USelectCharacterWidget::GetIsEnd()
{
    return bIsEnd;
}
