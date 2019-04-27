// The Green Heart @Politechnika Opolska

#include "SupermarketWidget.h"
#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"

#include "Structs/ToolOffer.h"
#include "Widgets/ToolOfferWidget.h"
#include "Widgets/AnimalOfferWidget.h"
#include "Widgets/ResourceOfferWidget.h"
#include "Fundamentals/FarmingGameMode.h"
#include "Structs/LevelInfo.h"
#include "Actors/Tools/Tool.h"
#include "Widgets/AmountOfferConfirmationWidget.h"

bool USupermarketWidget::Initialize()
{
	bool b = Super::Initialize();
	bStopAction = true;
	FOnInputAction Callback;
	Callback.BindUFunction(this, FName("CloseWidget"));
	ListenForInputAction("Interact", EInputEvent::IE_Pressed, false, Callback);
	return b;
}

void USupermarketWidget::SetupWidget(const FSupermarketInfo& NewSupermarketInfo)
{
	SupermarketInfo = NewSupermarketInfo;
	CreateConfirmationWidgetBindings();
	SetupSeedOffers(SupermarketInfo.OfferedSeeds);
	SetupAnimalOffers(SupermarketInfo.OfferedAnimals);
	SetupFeedOffers(SupermarketInfo.OfferedFeeds);
}

void USupermarketWidget::SetupSeedOffers(const TArray<FToolOffer>& Offers)
{
	for (int32 i = 0; i < Offers.Num(); i++)
	{
		UToolOfferWidget* OfferWidget = CreateWidget<UToolOfferWidget>(this, SeedOfferClass);
		OfferWidget->SetOfferInfo(Offers[i]);
		CreateOfferBindings(OfferWidget);
		OfferWidgets.Add(OfferWidget);

		SeedGrid->AddChild(OfferWidget);
		if (UUniformGridSlot* GridSlot = Cast<UUniformGridSlot>(OfferWidget->Slot))
		{
			GridSlot->SetColumn(i % SeedOffersInRow);
			GridSlot->SetRow(i / SeedOffersInRow);
		}
	}
}

void USupermarketWidget::SetupAnimalOffers(const TArray<FAnimalOffer>& Offers)
{
	for (int32 i = 0; i < Offers.Num(); i++)
	{
		UAnimalOfferWidget* OfferWidget = CreateWidget<UAnimalOfferWidget>(this, AnimalOfferClass);
		OfferWidget->SetOfferInfo(Offers[i]);
		CreateOfferBindings(OfferWidget);
		OfferWidgets.Add(OfferWidget);

		AnimalGrid->AddChild(OfferWidget);
		if (UUniformGridSlot* GridSlot = Cast<UUniformGridSlot>(OfferWidget->Slot))
		{
			GridSlot->SetColumn(i % AnimalOffersInRow);
			GridSlot->SetRow(i / AnimalOffersInRow);
		}
	}
}

void USupermarketWidget::SetupFeedOffers(const TArray<FResourceOffer>& Offers)
{
	for (int32 i = 0; i < Offers.Num(); i++)
	{
		UResourceOfferWidget* OfferWidget = CreateWidget<UResourceOfferWidget>(this, FeedOfferClass);
		OfferWidget->SetOfferInfo(Offers[i]);
		CreateAmountOfferBindings(OfferWidget);
		OfferWidgets.Add(OfferWidget);

		FeedGrid->AddChild(OfferWidget);
		if (UUniformGridSlot* GridSlot = Cast<UUniformGridSlot>(OfferWidget->Slot))
		{
			GridSlot->SetColumn(i % FeedOffersInRow);
			GridSlot->SetRow(i / FeedOffersInRow);
		}
	}
}

void USupermarketWidget::CreateOfferBindings(UOfferWidget* OfferWidget)
{
	OfferWidget->OnClicked.AddDynamic(this, &USupermarketWidget::OnOfferClicked);
}

void USupermarketWidget::CreateAmountOfferBindings(UResourceOfferWidget* OfferWidget)
{
	OfferWidget->OnClicked.AddDynamic(this, &USupermarketWidget::OnAmountOfferClicked);
}

void USupermarketWidget::CreateConfirmationWidgetBindings()
{
	OfferConfirmation->OnConfirm.AddDynamic(this, &USupermarketWidget::OnOfferConfirmed);
	OfferConfirmation->OnCancel.AddDynamic(this, &USupermarketWidget::OnOfferCanceled);
	AmountOfferConfirmation->OnConfirm.AddDynamic(this, &USupermarketWidget::OnAmountOfferConfirmed);
	AmountOfferConfirmation->OnCancel.AddDynamic(this, &USupermarketWidget::OnAmountOfferCanceled);
}

void USupermarketWidget::OnOfferClicked(UOfferWidget* ClickedOffer)
{
	ActiveOffer = ClickedOffer;
	SetupOfferConfirmationWidget(ClickedOffer);
	ShowOfferWidget();
}

void USupermarketWidget::OnAmountOfferClicked(UOfferWidget* ClickedOffer)
{
	if (UResourceOfferWidget* FeedOffer = Cast<UResourceOfferWidget>(ClickedOffer))
	{
		ActiveOffer = ClickedOffer;
		SetupAmountOfferConfirmationWidget(FeedOffer);
		ShowAmountOfferWidget();
	}
}

void USupermarketWidget::SetupOfferConfirmationWidget(UOfferWidget* Offer)
{
	OfferConfirmation->SetOfferName(Offer->GetOfferName());
	OfferConfirmation->SetOfferDescription(Offer->GetOfferDesctiprion());
	OfferConfirmation->SetOfferPrice(Offer->GetOfferPrice());
	OfferConfirmation->SetOfferThumbnail(Offer->GetThumbnail());
}

void USupermarketWidget::SetupAmountOfferConfirmationWidget(UOfferWidget* Offer)
{
	AmountOfferConfirmation->SetOfferName(Offer->GetOfferName());
	AmountOfferConfirmation->SetOfferDescription(Offer->GetOfferDesctiprion());
	AmountOfferConfirmation->SetOfferPrice(Offer->GetOfferPrice());
	AmountOfferConfirmation->SetOfferThumbnail(Offer->GetThumbnail());
	AmountOfferConfirmation->SetUnitPrice(Offer->GetOfferPrice());
}

void USupermarketWidget::OnOfferConfirmed()
{
	if (!ActiveOffer)
	{
		return;
	}

	ActiveOffer->Buy();
	UpdateWidgetState();

	HideOfferWidget();
	ActiveOffer = nullptr;
}

void USupermarketWidget::OnAmountOfferConfirmed(int32 Amount)
{
	if (!ActiveOffer)
	{
		return;
	}

	if (UResourceOfferWidget* FeedOffer = Cast<UResourceOfferWidget>(ActiveOffer))
	{
		FeedOffer->Buy(Amount);
	}
	UpdateWidgetState();

	HideAmountOfferWidget();
	ActiveOffer = nullptr;
}

void USupermarketWidget::OnOfferCanceled()
{
	HideOfferWidget();
}

void USupermarketWidget::OnAmountOfferCanceled()
{
	HideAmountOfferWidget();
}

void USupermarketWidget::UpdateWidgetState()
{
	for (UOfferWidget* OfferWidget : OfferWidgets)
	{
		OfferWidget->UpdateActivation();
	}
}

void USupermarketWidget::ShowOfferWidget()
{
	PlayAnimation(ShowOfferConfirmationAnimation, 0.0f, 1, EUMGSequencePlayMode::Forward);
}

void USupermarketWidget::HideOfferWidget()
{
	PlayAnimation(ShowOfferConfirmationAnimation, 0.0f, 1, EUMGSequencePlayMode::Reverse);
}

void USupermarketWidget::ShowAmountOfferWidget()
{
	PlayAnimation(ShowAmountOfferConfirmationAnimation, 0.0f, 1, EUMGSequencePlayMode::Forward);
}

void USupermarketWidget::HideAmountOfferWidget()
{
	PlayAnimation(ShowAmountOfferConfirmationAnimation, 0.0f, 1, EUMGSequencePlayMode::Reverse);
}

void USupermarketWidget::CloseWidget()
{
	RestoreGame();
	RemoveFromParent();
}

void USupermarketWidget::RestoreGame()
{
	if (AFarmingGameMode* GameMode = Cast<AFarmingGameMode>(GetWorld()->GetAuthGameMode()))
	{
		GameMode->RestoreGame();
	}
}