// The Green Heart @Politechnika Opolska

#include "BlacksmithWidget.h"
#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"
#include "Components/Button.h"
#include "Components/Image.h"

#include "Fundamentals/FarmingGameMode.h"
#include "Widgets/ToolOfferWidget.h"
#include "Widgets/OfferConfirmationWidget.h"
#include "Widgets/UpgradeConfirmationWidget.h"
#include "Structs/LevelInfo.h"
#include "Actors/Tools/Tool.h"

bool UBlacksmithWidget::Initialize()
{
	bool b = Super::Initialize();
	bStopAction = true;
	FOnInputAction Callback;
	Callback.BindUFunction(this, FName("CloseWidget"));
	ListenForInputAction("Interact", EInputEvent::IE_Pressed, false, Callback);
	return b;
}

void UBlacksmithWidget::SetupWidget(const FFarmerState& NewFarmerState, const FBlacksmithInfo& NewBlacksmithInfo)
{
	FarmerState = NewFarmerState;
	BlacksmithInfo = NewBlacksmithInfo;
	CreateConfirmationWidgetBindings();
	CreateUpgradeButtonBindings();
	SetupOffers(NewBlacksmithInfo.OfferedTools);
	SetupUpgrades();
}

void UBlacksmithWidget::CreateConfirmationWidgetBindings()
{
	OfferConfirmation->OnConfirm.AddDynamic(this, &UBlacksmithWidget::OnOfferConfirmed);
	OfferConfirmation->OnCancel.AddDynamic(this, &UBlacksmithWidget::OnOfferCanceled);
	UpgradeConfirmation->OnConfirm.AddDynamic(this, &UBlacksmithWidget::OnUpgradeConfirmed);
	UpgradeConfirmation->OnCancel.AddDynamic(this, &UBlacksmithWidget::OnUpgradeCanceled);
}

void UBlacksmithWidget::CreateUpgradeButtonBindings()
{
	UpgradeToolButton->OnClicked.AddDynamic(this, &UBlacksmithWidget::OnToolUpgradeClicked);
	UpgradeToolInventoryButton->OnClicked.AddDynamic(this, &UBlacksmithWidget::OnToolInventoryUpgradeClicked);
	UpgradeItemInventoryButton->OnClicked.AddDynamic(this, &UBlacksmithWidget::OnItemInventoryUpgradeClicked);
}

void UBlacksmithWidget::SetupOffers(const TArray<FToolOffer>& Offers)
{
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

void UBlacksmithWidget::SetupUpgrades()
{
	SetupToolUpgrade();
	SetupToolInventoryUpgrade();
	SetupItemInventoryUpgrade();
}

void UBlacksmithWidget::SetupToolUpgrade()
{
	if (AFarmingGameMode* GameMode = Cast<AFarmingGameMode>(GetWorld()->GetAuthGameMode()))
	{
		FToolInventoryState ToolInventory = FarmerState.ToolInventoryState;
		FToolInfo ToolInfo = ToolInventory.GetCurrentTool();
		ToolIcon->SetBrushFromTexture(ToolInfo.GetCurrentLevelInfo().Thumbnail);
		if (ToolInfo.Class && ToolInfo.CanUpgrade())
		{
			int32 UpgradeCost = ToolInfo.GetNextLevelInfo().Cost;
			bool bHasResources = GameMode->HasResource(EResourceType::Money, UpgradeCost);
			UpgradeToolButton->SetIsEnabled(bHasResources);
		}
		else
		{
			UpgradeToolButton->SetIsEnabled(false);
		}
	}
	else
	{
		UpgradeToolButton->SetIsEnabled(false);
	}
}

void UBlacksmithWidget::SetupToolInventoryUpgrade()
{
	if (AFarmingGameMode* GameMode = Cast<AFarmingGameMode>(GetWorld()->GetAuthGameMode()))
	{
		FToolInventoryState ToolInventory = FarmerState.ToolInventoryState;
		ToolInventoryIcon->SetBrushFromTexture(ToolInventory.GetCurrentLevelInfo().Thumbnail);
		if (ToolInventory.CanUpgrade())
		{
			int32 UpgradeCost = ToolInventory.GetNextLevelInfo().Cost;
			bool bHasResources = GameMode->HasResource(EResourceType::Money, UpgradeCost);
			UpgradeToolInventoryButton->SetIsEnabled(bHasResources);
		}
		else
		{
			UpgradeToolInventoryButton->SetIsEnabled(false);
		}
	}
	else
	{
		UpgradeToolInventoryButton->SetIsEnabled(false);
	}
}

void UBlacksmithWidget::SetupItemInventoryUpgrade()
{
	if (AFarmingGameMode* GameMode = Cast<AFarmingGameMode>(GetWorld()->GetAuthGameMode()))
	{
		FItemInventoryState ItemInventory = FarmerState.ItemInventoryState;
		ItemInventoryIcon->SetBrushFromTexture(ItemInventory.GetCurrentLevelInfo().Thumbnail);
		if (ItemInventory.CanUpgrade())
		{
			int32 UpgradeCost = ItemInventory.GetNextLevelInfo().Cost;
			bool bHasResources = GameMode->HasResource(EResourceType::Money, UpgradeCost);
			UpgradeItemInventoryButton->SetIsEnabled(bHasResources);
		}
		else
		{
			UpgradeItemInventoryButton->SetIsEnabled(false);
		}
	}
}

void UBlacksmithWidget::CreateOfferBindings(UToolOfferWidget* OfferWidget)
{
	OfferWidget->OnClicked.AddDynamic(this, &UBlacksmithWidget::OnOfferClicked);
}

void UBlacksmithWidget::OnOfferClicked(UOfferWidget* ClickedOffer)
{
	ActiveOffer = ClickedOffer;
	OfferConfirmation->SetOfferName(ActiveOffer->GetOfferName());
	OfferConfirmation->SetOfferDescription(ActiveOffer->GetOfferDesctiprion());
	OfferConfirmation->SetOfferPrice(ActiveOffer->GetOfferPrice());
	OfferConfirmation->SetOfferThumbnail(ActiveOffer->GetThumbnail());
	ShowOfferWidget();
}

void UBlacksmithWidget::OnOfferConfirmed()
{
	if (!ActiveOffer)
	{
		return;
	}

	if (UToolOfferWidget* ToolOffer = Cast<UToolOfferWidget>(ActiveOffer))
	{
		ToolOffer->SetAvailability(false);
	}
	ActiveOffer->Buy();

	UpdateWidgetState();
	HideOfferWidget();
	ActiveOffer = nullptr;
}

void UBlacksmithWidget::OnOfferCanceled()
{
	HideOfferWidget();
}

void UBlacksmithWidget::OnToolUpgradeClicked()
{
	ClickedUpgradeButton = UpgradeToolButton;
	FToolInventoryState ToolInventory = FarmerState.ToolInventoryState;
	FToolInfo CurrentTool = ToolInventory.GetCurrentTool();
	FText Name = CurrentTool.Name;
	FLevelInfo CurrentLevelInfo = CurrentTool.GetCurrentLevelInfo();
	FLevelInfo NextLevelInfo = CurrentTool.GetNextLevelInfo();
	int32 ToolLevel = CurrentTool.CurrentLevel;
	UpgradeConfirmation->SetupWidget(Name, CurrentLevelInfo, NextLevelInfo, ToolLevel);
	ShowUpgradeWidget();
}

void UBlacksmithWidget::OnToolInventoryUpgradeClicked()
{
	ClickedUpgradeButton = UpgradeToolInventoryButton;
	FToolInventoryState ToolInventory = FarmerState.ToolInventoryState;
	FText Name = FText::FromString("Tool Inventory");
	FLevelInfo CurrentLevelInfo = ToolInventory.GetCurrentLevelInfo();
	FLevelInfo NextLevelInfo = ToolInventory.GetNextLevelInfo();
	int32 ToolLevel = ToolInventory.Level;
	UpgradeConfirmation->SetupWidget(Name, CurrentLevelInfo, NextLevelInfo, ToolLevel);
	ShowUpgradeWidget();
}

void UBlacksmithWidget::OnItemInventoryUpgradeClicked()
{
	ClickedUpgradeButton = UpgradeItemInventoryButton;
	FItemInventoryState ItemInventory = FarmerState.ItemInventoryState;
	FText Name = FText::FromString("Item Inventory");
	FLevelInfo CurrentLevelInfo = ItemInventory.GetCurrentLevelInfo();
	FLevelInfo NextLevelInfo = ItemInventory.GetNextLevelInfo();
	int32 ItemLevel = ItemInventory.Level;
	UpgradeConfirmation->SetupWidget(Name, CurrentLevelInfo, NextLevelInfo, ItemLevel);
	ShowUpgradeWidget();
}

void UBlacksmithWidget::OnUpgradeConfirmed(int32 Price)
{
	if (AFarmingGameMode* GameMode = Cast<AFarmingGameMode>(GetWorld()->GetAuthGameMode()))
	{
		if (ClickedUpgradeButton == UpgradeToolButton)
		{
			GameMode->UpgradePlayerTool();
		}
		else if (ClickedUpgradeButton == UpgradeToolInventoryButton)
		{
			GameMode->UpgradePlayerToolInventory();
		}
		else if (ClickedUpgradeButton == UpgradeItemInventoryButton)
		{
			GameMode->UpgradePlayerItemInventory();
		}
		GameMode->RemoveResource(EResourceType::Money, Price);
		UpdateWidgetState();
		HideUpgradeWidget();
	}
}

void UBlacksmithWidget::OnUpgradeCanceled()
{
	ClickedUpgradeButton = nullptr;
	HideUpgradeWidget();
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

void UBlacksmithWidget::ShowOfferWidget()
{
	PlayAnimation(ShowOfferConfirmationAnimation, 0.0f, 1, EUMGSequencePlayMode::Forward);
}

void UBlacksmithWidget::HideOfferWidget()
{
	PlayAnimation(ShowOfferConfirmationAnimation, 0.0f, 1, EUMGSequencePlayMode::Reverse);
}

void UBlacksmithWidget::ShowUpgradeWidget()
{
	PlayAnimation(ShowUpgradeConfirmationAnimation, 0.0f, 1, EUMGSequencePlayMode::Forward);
}

void UBlacksmithWidget::HideUpgradeWidget()
{
	PlayAnimation(ShowUpgradeConfirmationAnimation, 0.0f, 1, EUMGSequencePlayMode::Reverse);
}

void UBlacksmithWidget::UpdateWidgetState()
{
	if (AFarmingGameMode* GameMode = Cast<AFarmingGameMode>(GetWorld()->GetAuthGameMode()))
	{
		FarmerState = GameMode->GetPlayerState();
		SetupUpgrades();
		for (UToolOfferWidget* OfferWidget : OfferWidgets)
		{
			OfferWidget->UpdateActivation();
		}
	}
}