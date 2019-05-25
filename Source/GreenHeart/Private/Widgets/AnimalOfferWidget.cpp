// The Green Heart @Politechnika Opolska

#include "AnimalOfferWidget.h"
#include "Components/Image.h"

#include "Enums/ResourceTypes.h"
#include "Fundamentals/FarmingGameMode.h"
#include "Widgets/Buttons/FocusButton.h"

void UAnimalOfferWidget::SetOfferInfo(const FAnimalOffer& NewOffer)
{
	AnimalOffer = NewOffer;
	Thumbnail->SetBrushFromTexture(NewOffer.Thumbnail);
	SetPriceText(NewOffer.Cost);
	UpdateActivation();
}

FAnimalOffer UAnimalOfferWidget::GetOfferInfo()
{
	return AnimalOffer;
}

void UAnimalOfferWidget::UpdateActivation()
{
	if (AFarmingGameMode* GameMode = GetWorld()->GetAuthGameMode<AFarmingGameMode>())
	{
		if (!GameMode->CanBuyAnimal(AnimalOffer.AnimalType))
		{
			Button->SetIsEnabled(false);
			return;
		}
	}

	Super::UpdateActivation();
}

void UAnimalOfferWidget::Buy()
{
	if (AFarmingGameMode* GameMode = GetWorld()->GetAuthGameMode<AFarmingGameMode>())
	{
		GameMode->RemoveResource(EResourceType::Money, AnimalOffer.Cost);
		GameMode->AddAnimal(AnimalOffer.AnimalType);
	}
}

FText UAnimalOfferWidget::GetOfferName()
{
	return AnimalOffer.Name;
}

FText UAnimalOfferWidget::GetOfferDesctiprion()
{
	return AnimalOffer.Description;
}

int32 UAnimalOfferWidget::GetOfferPrice()
{
	return AnimalOffer.Cost;
}

UTexture2D* UAnimalOfferWidget::GetThumbnail()
{
	return AnimalOffer.Thumbnail;
}


