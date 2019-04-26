// The Green Heart @Politechnika Opolska

#include "BlacksmithWidget.h"
#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"

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
	SetupOffers(NewInfo.OfferedTools);
}

void UBlacksmithWidget::SetupOffers(const TArray<FToolOffer>& Offers)
{
	OfferConfirmation->OnConfirm.AddDynamic(this, &UBlacksmithWidget::OnOfferConfirmed);
	OfferConfirmation->OnCancel.AddDynamic(this, &UBlacksmithWidget::OnOfferCanceled);

	for (int32 i = 0; i < Offers.Num(); i++)
	{
		UToolOfferWidget* OfferWidget = CreateWidget<UToolOfferWidget>(this, OfferClass);
		OfferWidget->SetOffer(Offers[i]);
		CreateOfferBindings(OfferWidget);

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
	PlayAnimation(ShowOfferConfirmationAnimation, 0.0f, 1, EUMGSequencePlayMode::Forward);
}

void UBlacksmithWidget::OnOfferConfirmed()
{
	UE_LOG(LogTemp,Warning,TEXT("OK"))
}

void UBlacksmithWidget::OnOfferCanceled()
{
	PlayAnimation(ShowOfferConfirmationAnimation, 0.0f, 1, EUMGSequencePlayMode::Reverse);
}