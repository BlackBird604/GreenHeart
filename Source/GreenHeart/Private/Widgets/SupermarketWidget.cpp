// The Green Heart @Politechnika Opolska

#include "SupermarketWidget.h"
#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"

#include "Structs/ToolOffer.h"
#include "Widgets/ToolOfferWidget.h"
#include "Fundamentals/FarmingGameMode.h"
#include "Structs/LevelInfo.h"
#include "Actors/Tools/Tool.h"
#include "Widgets/OfferConfirmationWidget.h"

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
	SetupOffers(SupermarketInfo.OfferedSeeds);
}

void USupermarketWidget::SetupOffers(const TArray<FToolOffer>& Offers)
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
			GridSlot->SetColumn(i % OffersInRow);
			GridSlot->SetRow(i / OffersInRow);
		}
	}
}

void USupermarketWidget::CreateOfferBindings(UToolOfferWidget* OfferWidget)
{
	OfferWidget->OnClicked.AddDynamic(this, &USupermarketWidget::OnOfferClicked);
}

void USupermarketWidget::CreateConfirmationWidgetBindings()
{
	OfferConfirmation->OnConfirm.AddDynamic(this, &USupermarketWidget::OnOfferConfirmed);
	OfferConfirmation->OnCancel.AddDynamic(this, &USupermarketWidget::OnOfferCanceled);
}

void USupermarketWidget::OnOfferClicked(UOfferWidget* ClickedOffer)
{
	ActiveOffer = ClickedOffer;
	SetupOfferConfirmationWidget(ClickedOffer);
	ShowOfferWidget();
}

void USupermarketWidget::SetupOfferConfirmationWidget(UOfferWidget* Offer)
{
	OfferConfirmation->SetOfferName(Offer->GetOfferName());
	OfferConfirmation->SetOfferDescription(Offer->GetOfferDesctiprion());
	OfferConfirmation->SetOfferPrice(Offer->GetOfferPrice());
	OfferConfirmation->SetOfferThumbnail(Offer->GetThumbnail());
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

void USupermarketWidget::OnOfferCanceled()
{
	HideOfferWidget();
}

void USupermarketWidget::UpdateWidgetState()
{
	for (UToolOfferWidget* OfferWidget : OfferWidgets)
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