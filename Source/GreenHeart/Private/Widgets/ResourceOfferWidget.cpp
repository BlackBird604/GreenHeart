// The Green Heart @Politechnika Opolska

#include "ResourceOfferWidget.h"

#include "Enums/ResourceTypes.h"
#include "Fundamentals/FarmingGameMode.h"

void UResourceOfferWidget::SetOfferInfo(const FResourceOffer& NewOffer)
{
	ResourceOffer = NewOffer;

	UpdateActivation();
}

FResourceOffer UResourceOfferWidget::GetOfferInfo()
{
	return ResourceOffer;
}

void UResourceOfferWidget::UpdateActivation()
{
	Super::UpdateActivation();
}

void UResourceOfferWidget::Buy()
{
	Buy(1);
}

void UResourceOfferWidget::Buy(int32 Amount)
{
	if (AFarmingGameMode* GameMode = GetWorld()->GetAuthGameMode<AFarmingGameMode>())
	{
		GameMode->RemoveResource(EResourceType::Money, ResourceOffer.Cost * Amount);
		GameMode->AddResource(ResourceOffer.ResourceType, Amount);
	}
}

FText UResourceOfferWidget::GetOfferName()
{
	return ResourceOffer.Name;
}

FText UResourceOfferWidget::GetOfferDesctiprion()
{
	return ResourceOffer.Description;
}

int32 UResourceOfferWidget::GetOfferPrice()
{
	return ResourceOffer.Cost;
}

UTexture2D* UResourceOfferWidget::GetThumbnail()
{
	return ResourceOffer.Thumbnail;
}