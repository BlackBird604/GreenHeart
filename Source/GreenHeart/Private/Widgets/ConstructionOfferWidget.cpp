// The Green Heart @Politechnika Opolska

#include "ConstructionOfferWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

#include "Fundamentals/FarmingGameMode.h"

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
	FString PriceString = FString::FromInt(GetOfferPrice());
	FText NewText = FText::FromString(PriceString + "G");
	PriceText->SetText(NewText);
	Thumbnail->SetBrushFromTexture(GetThumbnail());
}

void UConstructionOfferWidget::UpdateActivation()
{
	//TODO Check Building States

	Super::UpdateActivation();
}

void UConstructionOfferWidget::Buy()
{
	if (AFarmingGameMode* GameMode = GetWorld()->GetAuthGameMode<AFarmingGameMode>())
	{
		GameMode->RemoveResource(EResourceType::Money, GetOfferPrice());
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
