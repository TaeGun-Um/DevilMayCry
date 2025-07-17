// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectCharacterWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/TextBlock.h"

bool USelectCharacterWidget::Initialize()
{
    Super::Initialize();
    VariableSetting();

    CharacterType = ECharacterType::None;

    return true;
}

void USelectCharacterWidget::NeroButtonClicked()
{
    SetIsEnd();
    ResetNeroSelect();
    ResetVergilSelect();
    CharacterType = ECharacterType::None;
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
        ResetVergilSelect();
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
    ResetNeroSelect();
    ResetVergilSelect();
    CharacterType = ECharacterType::None;
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
        ResetNeroSelect();
    }

    CharacterType = ECharacterType::Vergil;
    PlayAnimation(VergilSelectAnimation);
}

void USelectCharacterWidget::VergilButtonUnHovered()
{
    SetUnHovered();
}

void USelectCharacterWidget::ResetNeroSelect()
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
    UCanvasPanelSlot* NeroTegImageSlot = Cast<UCanvasPanelSlot>(NeroTegImage->Slot);
    if (NeroTegImageSlot)
    {
        NeroTegImageSlot->SetSize(FVector2D(480.f, 120.f));
    }
    UCanvasPanelSlot* NeroLineImageSlot = Cast<UCanvasPanelSlot>(NeroLineImage->Slot);
    if (NeroLineImageSlot)
    {
        NeroLineImageSlot->SetSize(FVector2D(240.f, 4.f));
    }
    UCanvasPanelSlot* NeroTextSlot = Cast<UCanvasPanelSlot>(NeroTextBox->Slot);
    if (NeroTextSlot)
    {
        NeroTextSlot->SetPosition(FVector2D(-380.0f, 155.f));
    }
    UCanvasPanelSlot* NeroEXTextSlot = Cast<UCanvasPanelSlot>(NeroExTextBox->Slot);
    if (NeroEXTextSlot)
    {
        NeroEXTextSlot->SetPosition(FVector2D(-380.0f, 120.f));
    }

    NeroMaterial->SetScalarParameterValue(FName("ColorAmount"), 0.0f);
    NeroBackMaterial->SetScalarParameterValue(FName("ColorAmount"), 0.0f);
    NeroTagMaterial->SetScalarParameterValue(FName("ColorAmount"), 0.0f);
    NeroLineMaterial->SetScalarParameterValue(FName("ColorAmount"), 0.0f);
    NeroTextBox->SetColorAndOpacity(FSlateColor(FLinearColor(0.3f, 0.3f, 0.3f, 1.0f)));
    NeroExTextBox->SetColorAndOpacity(FSlateColor(FLinearColor(0.3f, 0.3f, 0.3f, 1.0f)));
}

void USelectCharacterWidget::ResetVergilSelect()
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
    UCanvasPanelSlot* VergilTegImageSlot = Cast<UCanvasPanelSlot>(VergilTegImage->Slot);
    if (VergilTegImageSlot)
    {
        VergilTegImageSlot->SetSize(FVector2D(480.f, 120.f));
    }
    UCanvasPanelSlot* VergilLineImageSlot = Cast<UCanvasPanelSlot>(VergilLineImage->Slot);
    if (VergilLineImageSlot)
    {
        VergilLineImageSlot->SetSize(FVector2D(240.f, 4.f));
    }
    UCanvasPanelSlot* VergilTextSlot = Cast<UCanvasPanelSlot>(VergilTextBox->Slot);
    if (VergilTextSlot)
    {
        VergilTextSlot->SetPosition(FVector2D(420.0f, 155.f));
    }
    UCanvasPanelSlot* VergilEXTextSlot = Cast<UCanvasPanelSlot>(VergilExTextBox->Slot);
    if (VergilEXTextSlot)
    {
        VergilEXTextSlot->SetPosition(FVector2D(420.0f, 120.f));
    }

    VergilMaterial->SetScalarParameterValue(FName("ColorAmount"), 0.0f);
    VergilBackMaterial->SetScalarParameterValue(FName("ColorAmount"), 0.0f);
    VergilTagMaterial->SetScalarParameterValue(FName("ColorAmount"), 0.0f);
    VergilLineMaterial->SetScalarParameterValue(FName("ColorAmount"), 0.0f);
    VergilTextBox->SetColorAndOpacity(FSlateColor(FLinearColor(0.3f, 0.3f, 0.3f, 1.0f)));
    VergilExTextBox->SetColorAndOpacity(FSlateColor(FLinearColor(0.3f, 0.3f, 0.3f, 1.0f)));
}

void USelectCharacterWidget::VariableSetting()
{
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

    if (NeroTegImage)
    {
        UCanvasPanelSlot* NeroTagImageSlot = Cast<UCanvasPanelSlot>(NeroTegImage->Slot);
        if (NeroTagImageSlot)
        {
            NeroTagImageSlot->SetAnchors(FAnchors(0.5f, 0.5f)); // Button Center Ref.
            NeroTagImageSlot->SetAlignment(FVector2D(0.5f, 0.5f)); // Alignment
            NeroTagImageSlot->SetPosition(FVector2D(-380.0f, 150.f));
            NeroTagImageSlot->SetSize(FVector2D(480.f, 120.f));
        }

        UMaterialInterface* BaseMaterial = Cast<UMaterialInterface>(StaticLoadObject(UMaterialInterface::StaticClass(), nullptr,
            TEXT("/Game/UI/Select/MI_Graysclae_NeroTag")));
        if (BaseMaterial)
        {
            NeroTagMaterial = UMaterialInstanceDynamic::Create(BaseMaterial, this);
            NeroTegImage->SetBrushFromMaterial(NeroTagMaterial);
        }
    }

    if (NeroLineImage)
    {
        UCanvasPanelSlot* NeroLineImageSlot = Cast<UCanvasPanelSlot>(NeroLineImage->Slot);
        if (NeroLineImageSlot)
        {
            NeroLineImageSlot->SetAnchors(FAnchors(0.5f, 0.5f)); // Button Center Ref.
            NeroLineImageSlot->SetAlignment(FVector2D(0.5f, 0.5f)); // Alignment
            NeroLineImageSlot->SetPosition(FVector2D(-380.0f, 140.f));
            NeroLineImageSlot->SetSize(FVector2D(240.f, 4.f));
        }

        UMaterialInterface* BaseMaterial = Cast<UMaterialInterface>(StaticLoadObject(UMaterialInterface::StaticClass(), nullptr,
            TEXT("/Game/UI/Select/MI_Graysclae_NeroLine")));
        if (BaseMaterial)
        {
            NeroLineMaterial = UMaterialInstanceDynamic::Create(BaseMaterial, this);
            NeroLineImage->SetBrushFromMaterial(NeroLineMaterial);
        }
    }

    if (VergilTegImage)
    {
        UCanvasPanelSlot* VergilTegImageSlot = Cast<UCanvasPanelSlot>(VergilTegImage->Slot);
        if (VergilTegImageSlot)
        {
            VergilTegImageSlot->SetAnchors(FAnchors(0.5f, 0.5f)); // Button Center Ref.
            VergilTegImageSlot->SetAlignment(FVector2D(0.5f, 0.5f)); // Alignment
            VergilTegImageSlot->SetPosition(FVector2D(420.0f, 150.f));
            VergilTegImageSlot->SetSize(FVector2D(480.f, 120.f));
        }

        UMaterialInterface* BaseMaterial = Cast<UMaterialInterface>(StaticLoadObject(UMaterialInterface::StaticClass(), nullptr,
            TEXT("/Game/UI/Select/MI_Graysclae_VergilTag")));
        if (BaseMaterial)
        {
            VergilTagMaterial = UMaterialInstanceDynamic::Create(BaseMaterial, this);
            VergilTegImage->SetBrushFromMaterial(VergilTagMaterial);
        }
    }

    if (VergilLineImage)
    {
        UCanvasPanelSlot* VergilLineImageSlot = Cast<UCanvasPanelSlot>(VergilLineImage->Slot);
        if (VergilLineImageSlot)
        {
            VergilLineImageSlot->SetAnchors(FAnchors(0.5f, 0.5f)); // Button Center Ref.
            VergilLineImageSlot->SetAlignment(FVector2D(0.5f, 0.5f)); // Alignment
            VergilLineImageSlot->SetPosition(FVector2D(420.0f, 140.f));
            VergilLineImageSlot->SetSize(FVector2D(240.f, 4.f));
        }

        UMaterialInterface* BaseMaterial = Cast<UMaterialInterface>(StaticLoadObject(UMaterialInterface::StaticClass(), nullptr,
            TEXT("/Game/UI/Select/MI_Graysclae_VergilLine")));
        if (BaseMaterial)
        {
            VergilLineMaterial = UMaterialInstanceDynamic::Create(BaseMaterial, this);
            VergilLineImage->SetBrushFromMaterial(VergilLineMaterial);
        }
    }

    UCanvasPanelSlot* NeroEXTextSlot = Cast<UCanvasPanelSlot>(NeroExTextBox->Slot);
    if (NeroEXTextSlot)
    {
        NeroEXTextSlot->SetAnchors(FAnchors(0.5f, 0.5f)); // Button Center Ref.
        NeroEXTextSlot->SetAlignment(FVector2D(0.5f, 0.5f)); // Alignment
        NeroEXTextSlot->SetPosition(FVector2D(-380.0f, 120.f));
        NeroEXTextSlot->SetSize(FVector2D(300.f, 50.f));

        FSlateFontInfo FontInfo;
        FontInfo.FontObject = LoadObject<UObject>(nullptr, TEXT("/Game/Asset/Font/DMC5Font_Font"));
        FontInfo.TypefaceFontName = FName("Default");
        FontInfo.Size = 24;
        FontInfo.LetterSpacing = 100;

        NeroExTextBox->SetFont(FontInfo);
        NeroExTextBox->SetJustification(ETextJustify::Center);
        NeroExTextBox->SetText(FText::FromString(TEXT("The Devil Hunter")));
        NeroExTextBox->SetColorAndOpacity(FSlateColor(FLinearColor(0.3f, 0.3f, 0.3f, 1.0f)));
    }

    UCanvasPanelSlot* NeroTextSlot = Cast<UCanvasPanelSlot>(NeroTextBox->Slot);
    if (NeroTextSlot)
    {
        NeroTextSlot->SetAnchors(FAnchors(0.5f, 0.5f)); // Button Center Ref.
        NeroTextSlot->SetAlignment(FVector2D(0.5f, 0.5f)); // Alignment
        NeroTextSlot->SetPosition(FVector2D(-380.0f, 155.f));
        NeroTextSlot->SetSize(FVector2D(300.f, 50.f));

        FSlateFontInfo FontInfo;
        FontInfo.FontObject = LoadObject<UObject>(nullptr, TEXT("/Game/Asset/Font/DMC5Font_Font"));
        FontInfo.TypefaceFontName = FName("Default");
        FontInfo.Size = 48;
        FontInfo.LetterSpacing = 100;

        NeroTextBox->SetFont(FontInfo);
        NeroTextBox->SetJustification(ETextJustify::Center);
        NeroTextBox->SetText(FText::FromString(TEXT("NERO")));
        NeroTextBox->SetColorAndOpacity(FSlateColor(FLinearColor(0.3f, 0.3f, 0.3f, 1.0f)));
    }

    UCanvasPanelSlot* VergilEXTextSlot = Cast<UCanvasPanelSlot>(VergilExTextBox->Slot);
    if (VergilEXTextSlot)
    {
        VergilEXTextSlot->SetAnchors(FAnchors(0.5f, 0.5f)); // Button Center Ref.
        VergilEXTextSlot->SetAlignment(FVector2D(0.5f, 0.5f)); // Alignment
        VergilEXTextSlot->SetPosition(FVector2D(420.0f, 120.f));
        VergilEXTextSlot->SetSize(FVector2D(300.f, 50.f));

        FSlateFontInfo FontInfo;
        FontInfo.FontObject = LoadObject<UObject>(nullptr, TEXT("/Game/Asset/Font/DMC5Font_Font"));
        FontInfo.TypefaceFontName = FName("Default");
        FontInfo.Size = 24;
        FontInfo.LetterSpacing = 100;

        VergilExTextBox->SetFont(FontInfo);
        VergilExTextBox->SetJustification(ETextJustify::Center);
        VergilExTextBox->SetText(FText::FromString(TEXT("The Alpha and the Omega")));
        VergilExTextBox->SetColorAndOpacity(FSlateColor(FLinearColor(0.3f, 0.3f, 0.3f, 1.0f)));
    }

    UCanvasPanelSlot* VergilTextSlot = Cast<UCanvasPanelSlot>(VergilTextBox->Slot);
    if (NeroTextSlot)
    {
        VergilTextSlot->SetAnchors(FAnchors(0.5f, 0.5f)); // Button Center Ref.
        VergilTextSlot->SetAlignment(FVector2D(0.5f, 0.5f)); // Alignment
        VergilTextSlot->SetPosition(FVector2D(0.0f, 250.f));
        VergilTextSlot->SetPosition(FVector2D(420.0f, 155.f));
        VergilTextSlot->SetSize(FVector2D(300.f, 50.f));

        FSlateFontInfo FontInfo;
        FontInfo.FontObject = LoadObject<UObject>(nullptr, TEXT("/Game/Asset/Font/DMC5Font_Font"));
        FontInfo.TypefaceFontName = FName("Default");
        FontInfo.Size = 48;
        FontInfo.LetterSpacing = 100;

        VergilTextBox->SetFont(FontInfo);
        VergilTextBox->SetJustification(ETextJustify::Center);
        VergilTextBox->SetText(FText::FromString(TEXT("VERGIL")));
        VergilTextBox->SetColorAndOpacity(FSlateColor(FLinearColor(0.3f, 0.3f, 0.3f, 1.0f)));
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
}