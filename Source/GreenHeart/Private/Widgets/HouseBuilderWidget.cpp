// The Green Heart @Politechnika Opolska

#include "HouseBuilderWidget.h"
#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"

#include "Fundamentals/FarmingGameMode.h"
#include "Widgets/ConstructionOfferWidget.h"
#include "Widgets/UpgradeConfirmationWidget.h"
#include "Widgets/DescriptionWidget.h"

bool UHouseBuilderWidget::Initialize()
{
	bool b = Super::Initialize();
	bStopAction = true;
	FOnInputAction Callback;
	Callback.BindUFunction(this, FName("CloseWidget"));
	ListenForInputAction("Exit", EInputEvent::IE_Pressed, false, Callback);
	return b;
}

void UHouseBuilderWidget::SetupWidget(const TArray<FConstructionState>& NewConstructionStates)
{
	CreateConfirmationWidgetBindings();
	SetupConstructionOffers(NewConstructionStates);
	SetupFocus();
}

void UHouseBuilderWidget::SetupConstructionOffers(const TArray<FConstructionState>& Offers)
{
	for (int32 i = 0; i < Offers.Num(); i++)
	{
		UConstructionOfferWidget* OfferWidget = CreateWidget<UConstructionOfferWidget>(this, ConstructionOfferClass);
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

void UHouseBuilderWidget::SetupFocus()
{
	for (UOfferWidget* Offer : OfferWidgets)
	{
		if (Offer->IsEnabled())
		{
			Offer->SetupFocus();
			break;
		}
	}
}

void UHouseBuilderWidget::CreateConfirmationWidgetBindings()
{
	UpgradeConfirmation->OnConfirm.AddDynamic(this, &UHouseBuilderWidget::OnUpgradeConfirmed);
	UpgradeConfirmation->OnCancel.AddDynamic(this, &UHouseBuilderWidget::OnUpgradeCanceled);
}

void UHouseBuilderWidget::CreateOfferBindings(UOfferWidget* OfferWidget)
{
	OfferWidget->OnHovered.AddDynamic(this, &UHouseBuilderWidget::OnOfferHovered);
	OfferWidget->OnUnhovered.AddDynamic(this, &UHouseBuilderWidget::OnOfferUnhovered);
	OfferWidget->OnClicked.AddDynamic(this, &UHouseBuilderWidget::OnOfferClicked);
}

void UHouseBuilderWidget::OnOfferHovered(UOfferWidget* HoveredOffer)
{
	if (DescriptionBox)
	{
		DescriptionBox->SetText(HoveredOffer->GetOfferName(), HoveredOffer->GetOfferDesctiprion());
	}
}

void UHouseBuilderWidget::OnOfferUnhovered()
{
	if (DescriptionBox)
	{
		DescriptionBox->ClearText();
	}
}

void UHouseBuilderWidget::OnOfferClicked(UOfferWidget* ClickedOffer)
{
	if (UConstructionOfferWidget* ConstructionOffer = Cast<UConstructionOfferWidget>(ClickedOffer))
	{
		ActiveOffer = ConstructionOffer;
		SetupUpgradeConfirmationWidget(ConstructionOffer);
		ShowUpgradeConfirmationWidget();
	}
}

void UHouseBuilderWidget::SetupUpgradeConfirmationWidget(UConstructionOfferWidget* ClickedOffer)
{
	FText Name = ClickedOffer->GetOfferName();
	FLevelInfo CurrentLevelInfo = ClickedOffer->GetCurrentLevelInfo();
	FLevelInfo NextLevelInfo = ClickedOffer->GetNextLevelInfo();
	int32 CurrentLevel = ClickedOffer->GetCurrentLevel();
	UpgradeConfirmation->SetupWidget(Name, CurrentLevelInfo, NextLevelInfo, CurrentLevel);
}

void UHouseBuilderWidget::OnUpgradeConfirmed(int32 Price)
{
	if (!ActiveOffer)
	{
		return;
	}

	ActiveOffer->Buy();
	CloseWidget();
}

void UHouseBuilderWidget::OnUpgradeCanceled()
{
	HideUpgradeConfirmationWidget();
}

void UHouseBuilderWidget::ShowUpgradeConfirmationWidget()
{
	UpgradeConfirmation->SetupFocus();
	PlayAnimation(ShowUpgradeConfirmationAnimation, 0.0f, 1, EUMGSequencePlayMode::Forward);
}

void UHouseBuilderWidget::HideUpgradeConfirmationWidget()
{
	SetupFocus();
	PlayAnimation(ShowUpgradeConfirmationAnimation, 0.0f, 1, EUMGSequencePlayMode::Reverse);
}

void UHouseBuilderWidget::CloseWidget()
{
	RestoreGame();
	RemoveFromParent();
}

void UHouseBuilderWidget::RestoreGame()
{
	if (AFarmingGameMode* GameMode = Cast<AFarmingGameMode>(GetWorld()->GetAuthGameMode()))
	{
		GameMode->RestoreGame();
	}
}