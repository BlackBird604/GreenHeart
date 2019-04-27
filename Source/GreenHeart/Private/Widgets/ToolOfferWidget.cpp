// The Green Heart @Politechnika Opolska

#include "ToolOfferWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"

#include "Structs/LevelInfo.h"
#include "Actors/Tools/Tool.h"
#include "Fundamentals/FarmingGameMode.h"


void UToolOfferWidget::SetOfferInfo(const FToolOffer& NewOffer)
{
	ToolOffer = NewOffer;
	SetDefaults(ToolOffer.OfferedClass);
	UpdateActivation();
}

void UToolOfferWidget::SetDefaults(TSubclassOf<ATool> ToolClass)
{
	if (ToolClass)
	{
		ATool* DefaultTool = Cast<ATool>(ToolClass->GetDefaultObject());
		if (DefaultTool)
		{
			ToolInfo = DefaultTool->GetToolInfo();

			FLevelInfo LevelInfo = ToolInfo.GetFirstLevelInfo();
			OfferPrice = LevelInfo.Cost;
			OfferThumbnail = LevelInfo.Thumbnail;

			Thumbnail->SetBrushFromTexture(OfferThumbnail);
		}
	}
}

FToolOffer UToolOfferWidget::GetOfferInfo()
{
	return ToolOffer;
}

void UToolOfferWidget::UpdateActivation()
{
	if (!ToolOffer.OfferedClass || !ToolOffer.bIsAvaliable)
	{
		Button->SetIsEnabled(false);
		return;
	}

	Super::UpdateActivation();
}

void UToolOfferWidget::Buy()
{
	if (AFarmingGameMode* GameMode = GetWorld()->GetAuthGameMode<AFarmingGameMode>())
	{
		GameMode->RemoveResource(EResourceType::Money, OfferPrice);
		GameMode->AddNewTool(ToolInfo);
	}
}

FText UToolOfferWidget::GetOfferName()
{
	return ToolInfo.Name;
}

FText UToolOfferWidget::GetOfferDesctiprion()
{
	return ToolInfo.Description;
}

int32 UToolOfferWidget::GetOfferPrice()
{
	return OfferPrice;
}

UTexture2D* UToolOfferWidget::GetThumbnail()
{
	return OfferThumbnail;
}

void UToolOfferWidget::SetAvailability(bool bNewAvalable)
{
	ToolOffer.bIsAvaliable = bNewAvalable;
}