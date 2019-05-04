// The Green Heart @Politechnika Opolska

#include "AmountOfferConfirmationWidget.h"
#include "Components/TextBlock.h"
#include "TimerManager.h"

#include "Enums/ResourceTypes.h"
#include "Fundamentals/FarmingGameMode.h"
#include "Widgets/Buttons/FocusButton.h"

bool UAmountOfferConfirmationWidget::Initialize()
{
	bool b = Super::Initialize();
	IncreaseAmountButton->OnPressed.AddDynamic(this, &UAmountOfferConfirmationWidget::OnIncreaseButtonClicked);
	IncreaseAmountButton->OnReleased.AddDynamic(this, &UAmountOfferConfirmationWidget::OnIncreaseButtonReleased);
	DecreaseAmountButton->OnPressed.AddDynamic(this, &UAmountOfferConfirmationWidget::OnDecreaseButtonClicked);
	DecreaseAmountButton->OnReleased.AddDynamic(this, &UAmountOfferConfirmationWidget::OnDecreaseButtonReleased);
	IncreaseAmountButton->StartUpdating();
	DecreaseAmountButton->StartUpdating();
	GameMode = GetWorld()->GetAuthGameMode<AFarmingGameMode>();
	return b;
}

void UAmountOfferConfirmationWidget::SetUnitPrice(int32 NewPrice)
{
	UnitPrice = NewPrice;
	CurrentAmount = 1;
	UpdateWidget();
}

void UAmountOfferConfirmationWidget::OnIncreaseButtonClicked()
{
	IncreaseAmount();
	GetWorld()->GetTimerManager().SetTimer(AmountUpdateTimer, this, &UAmountOfferConfirmationWidget::IncreaseAmount, AmountUpdateRate, true, AmountUpdateInitialDelay);
}

void UAmountOfferConfirmationWidget::OnIncreaseButtonReleased()
{
	GetWorld()->GetTimerManager().ClearTimer(AmountUpdateTimer);
}

void UAmountOfferConfirmationWidget::OnDecreaseButtonClicked()
{
	DecreaseAmount();
	GetWorld()->GetTimerManager().SetTimer(AmountUpdateTimer, this, &UAmountOfferConfirmationWidget::DecreaseAmount, AmountUpdateRate, true, AmountUpdateInitialDelay);
}

void UAmountOfferConfirmationWidget::OnDecreaseButtonReleased()
{
	GetWorld()->GetTimerManager().ClearTimer(AmountUpdateTimer);
}

void UAmountOfferConfirmationWidget::IncreaseAmount()
{
	if (CurrentAmount < MaxAmount)
	{
		CurrentAmount++;
		UpdateWidget();
	}
}


void UAmountOfferConfirmationWidget::DecreaseAmount()
{
	if (CurrentAmount > 1)
	{
		CurrentAmount--;
		UpdateWidget();
	}
}

void UAmountOfferConfirmationWidget::UpdateWidget()
{
	if (GameMode)
	{
		int32 TotalCost = CurrentAmount * UnitPrice;
		SetOfferPrice(TotalCost);
		AmountText->SetText(FText::AsNumber(CurrentAmount));
		bool bHasResources = GameMode->HasResource(EResourceType::Money, TotalCost);
		ConfirmButton->SetIsEnabled(bHasResources);
	}
}

void UAmountOfferConfirmationWidget::OnConfirmButtonClicked()
{
	OnConfirm.Broadcast(CurrentAmount);
}