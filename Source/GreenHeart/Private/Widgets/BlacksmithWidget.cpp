// The Green Heart @Politechnika Opolska

#include "BlacksmithWidget.h"
#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"

#include "Fundamentals/FarmingGameMode.h"
#include "Widgets/ToolOfferWidget.h"
#include "Widgets/OfferConfirmationWidget.h"

bool UBlacksmithWidget::Initialize()
{
	bool b = Super::Initialize();
	bStopAction = true;
	FOnInputAction Callback;
	Callback.BindUFunction(this, FName("CloseWidget"));
	ListenForInputAction("Interact", EInputEvent::IE_Pressed, false, Callback);
	return b;
}

void UBlacksmithWidget::SetupWidget(const FBlacksmithInfo& NewInfo)
{
	BlacksmithInfo = NewInfo;
	SetupOffers(NewInfo.OfferedTools);
}

void UBlacksmithWidget::SetupOffers(const TArray<FToolOffer>& Offers)
{
	OfferConfirmation->OnConfirm.AddDynamic(this, &UBlacksmithWidget::OnOfferConfirmed);
	OfferConfirmation->OnCancel.AddDynamic(this, &UBlacksmithWidget::OnOfferCanceled);

	for (int32 i = 0; i < Offers.Num(); i++)
	{
		UToolOfferWidget* OfferWidget = CreateWidget<UToolOfferWidget>(this, OfferClass);
		OfferWidget->SetOfferInfo(Offers[i]);
		CreateOfferBindings(OfferWidget);
		OfferWidgets.Add(OfferWidget);

		OfferGrid->AddChild(OfferWidget);
		if (UUniformGridSlot* GridSlot = Cast<UUniformGridSlot>(OfferWidget->Slot))
		{
			GridSlot->SetColumn(i % OffersInRow);
			GridSlot->SetRow(i / OffersInRow);
		}
	}
}

void UBlacksmithWidget::CreateOfferBindings(UToolOfferWidget* OfferWidget)
{
	OfferWidget->OnClicked.AddDynamic(this, &UBlacksmithWidget::OnOfferClicked);
}

void UBlacksmithWidget::OnOfferClicked(UToolOfferWidget* ClickedOffer)
{
	ActiveOffer = ClickedOffer;
	OfferConfirmation->SetOfferPrice(ActiveOffer->GetOfferPrice());
	OfferConfirmation->SetOfferThumbnail(ActiveOffer->GetThumbnail());
	PlayAnimation(ShowOfferConfirmationAnimation, 0.0f, 1, EUMGSequencePlayMode::Forward);
}

void UBlacksmithWidget::OnOfferConfirmed()
{
	if (!ActiveOffer)
	{
		return;
	}

	ActiveOffer->SetAvailability(false);
	ActiveOffer->Buy();

	for (UToolOfferWidget* OfferWidget : OfferWidgets)
	{
		OfferWidget->UpdateActivation();
	}
	PlayAnimation(ShowOfferConfirmationAnimation, 0.0f, 1, EUMGSequencePlayMode::Reverse);
	ActiveOffer = nullptr;
}

void UBlacksmithWidget::OnOfferCanceled()
{
	PlayAnimation(ShowOfferConfirmationAnimation, 0.0f, 1, EUMGSequencePlayMode::Reverse);
}

void UBlacksmithWidget::CloseWidget()
{
	RestoreGame();
	SaveBlacksmithInfo();
	RemoveFromParent();
}

void UBlacksmithWidget::SaveBlacksmithInfo()
{
	if (AFarmingGameMode* GameMode = Cast<AFarmingGameMode>(GetWorld()->GetAuthGameMode()))
	{
		TArray<FToolOffer> NewToolOffers;
		for (UToolOfferWidget* OfferWidget : OfferWidgets)
		{
			NewToolOffers.Add(OfferWidget->GetOfferInfo());
		}
		BlacksmithInfo.OfferedTools = NewToolOffers;
		GameMode->UpdateBlacksmithInfo(BlacksmithInfo);
	}
}

void UBlacksmithWidget::RestoreGame()
{
	if (AFarmingGameMode* GameMode = Cast<AFarmingGameMode>(GetWorld()->GetAuthGameMode()))
	{
		GameMode->RestoreGame();
	}
}