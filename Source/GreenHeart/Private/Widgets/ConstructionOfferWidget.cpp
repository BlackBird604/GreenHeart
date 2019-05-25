// The Green Heart @Politechnika Opolska

#include "ConstructionOfferWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

#include "Fundamentals/FarmingGameMode.h"
#include "Widgets/Buttons/FocusButton.h"

void UConstructionOfferWidget::SetOfferInfo(const FConstructionState& NewOffer)
{
	ConstructionOffer = NewOffer;

	SetupWidgetComponents();
	UpdateActivation();
}

FConstructionState UConstructionOfferWidget::GetOfferInfo()
{
	return ConstructionOffer;
}

void UConstructionOfferWidget::SetupWidgetComponents()
{
	NameText->SetText(ConstructionOffer.Name);
	SetPriceText(GetOfferPrice());
	Thumbnail->SetBrushFromTexture(GetThumbnail());
}

void UConstructionOfferWidget::UpdateActivation()
{
	if (!ConstructionOffer.CanBeUpgraded())
	{
		Button->SetIsEnabled(false);
		return;
	}

	Super::UpdateActivation();
}

void UConstructionOfferWidget::Buy()
{
	if (AFarmingGameMode* GameMode = GetWorld()->GetAuthGameMode<AFarmingGameMode>())
	{
		GameMode->RemoveResource(EResourceType::Money, GetOfferPrice());
		GameMode->StartConstructionUpgrade(ConstructionOffer.ConstructionType);
	}
}

FText UConstructionOfferWidget::GetOfferName()
{
	return ConstructionOffer.Name;
}

FText UConstructionOfferWidget::GetOfferDesctiprion()
{
	return ConstructionOffer.Description;
}

int32 UConstructionOfferWidget::GetOfferPrice()
{
	FBuildingLevelInfo NextLevelInfo = GetNextLevelInfo();
	return NextLevelInfo.Cost;
}

UTexture2D* UConstructionOfferWidget::GetThumbnail()
{
	FBuildingLevelInfo CurrentLevelInfo = GetCurrentLevelInfo();
	return CurrentLevelInfo.Thumbnail;
}

int32 UConstructionOfferWidget::GetCurrentLevel()
{
	return ConstructionOffer.CurrentLevel;
}

FBuildingLevelInfo UConstructionOfferWidget::GetCurrentLevelInfo()
{
	return ConstructionOffer.GetCurrentLevelInfo();
}

FBuildingLevelInfo UConstructionOfferWidget::GetNextLevelInfo()
{
	return ConstructionOffer.GetNextLevelInfo();
}
