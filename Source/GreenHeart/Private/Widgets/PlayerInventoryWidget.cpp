// The Green Heart @Politechnika Opolska

#include "PlayerInventoryWidget.h"
#include "Components/TextBlock.h"
#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"

#include "Widgets/InventoryToolSlotWidget.h"
#include "Widgets/InventoryItemSlotWidget.h"
#include "Widgets/DescriptionWidget.h"
#include "Fundamentals/FarmingGameMode.h"
#include "Characters/Farmer.h"

bool UPlayerInventoryWidget::Initialize()
{
	bool b = Super::Initialize();
	bStopAction = true;
	FOnInputAction Callback;
	Callback.BindUFunction(this, FName("CloseWidget"));
	ListenForInputAction("ToggleInventory", EInputEvent::IE_Pressed, false, Callback);
	ListenForInputAction("Exit", EInputEvent::IE_Pressed, false, Callback);
	return b;
}

void UPlayerInventoryWidget::SetCowInfo(int32 CowAmount, int32 MaxCowAmount)
{
	if (CowAmountText)
	{
		FText NewCowAmountText = FText::AsNumber(CowAmount);
		CowAmountText->SetText(NewCowAmountText);
	}

	if (MaxCowAmountText)
	{
		FText NewMaxCowAmountText = FText::AsNumber(MaxCowAmount);
		MaxCowAmountText->SetText(NewMaxCowAmountText);
	}
}

void UPlayerInventoryWidget::SetChickenInfo(int32 ChickenAmount, int32 MaxChickenAmount)
{
	if (ChickenAmountText)
	{
		FText NewChickenAmountText = FText::AsNumber(ChickenAmount);
		ChickenAmountText->SetText(NewChickenAmountText);
	}

	if (MaxChickenAmountText)
	{
		FText NewMaxChickenAmountText = FText::AsNumber(MaxChickenAmount);
		MaxChickenAmountText->SetText(NewMaxChickenAmountText);
	}
}

void UPlayerInventoryWidget::SetFeedInfo(int32 CowFeedAmount, int32 ChickenFeedAmount)
{
	if (CowFeedAmountText)
	{
		FText NewCowFeedAmountText = FText::AsNumber(CowFeedAmount);
		CowFeedAmountText->SetText(NewCowFeedAmountText);
	}

	if (ChickenFeedAmountText)
	{
		FText NewChickenFeedAmountText = FText::AsNumber(ChickenFeedAmount);
		ChickenFeedAmountText->SetText(NewChickenFeedAmountText);
	}
}

void UPlayerInventoryWidget::PopulateSlots(AFarmer* Farmer)
{
	PlayerRef = Farmer;
	FFarmerState FarmerState = Farmer->GetCurrentState();
	const TArray<FToolInfo>& ToolInfos = FarmerState.ToolInventoryState.ToolInfos;
	const TArray<FItemInfo>& ItemInfos = FarmerState.ItemInventoryState.ItemInfos;
	const FItemInfo& ItemInHands = FarmerState.ItemInHandsInfo;

	PopulateToolSlots(ToolInfos);
	PopulateItemSlots(ItemInHands, ItemInfos);
	CurrentToolSlot->SetupFocus();
}

void UPlayerInventoryWidget::PopulateToolSlots(const TArray<FToolInfo>& ToolInfos)
{
	if (ToolInfos.Num() == 0)
	{
		return;
	}

	CurrentToolSlot->SetToolInfo(ToolInfos[0]);
	CreateSlotBindings(CurrentToolSlot);

	for (int i = 1; i < ToolInfos.Num(); i++)
	{
		UInventoryToolSlotWidget* InventoryToolSlot = CreateWidget<UInventoryToolSlotWidget>(this, ToolSlotClass);
		InventoryToolSlot->SetToolInfo(ToolInfos[i]);
		CreateSlotBindings(InventoryToolSlot);
		ToolSlots.Add(InventoryToolSlot);

		ToolGrid->AddChild(InventoryToolSlot);
		if (UUniformGridSlot* GridSlot = Cast<UUniformGridSlot>(InventoryToolSlot->Slot))
		{
			GridSlot->SetColumn((i-1) % SlotsInRow);
			GridSlot->SetRow((i-1) / SlotsInRow);
		}
	}
}

void UPlayerInventoryWidget::PopulateItemSlots(const FItemInfo& ItemInHands, const TArray<FItemInfo>& ItemInfos)
{
	if (ItemInfos.Num() == 0)
	{
		return;
	}

	CurrentItemSlot->SetItemInfo(ItemInHands);
	CreateSlotBindings(CurrentItemSlot);

	for (int i = 0; i < ItemInfos.Num(); i++)
	{
		UInventoryItemSlotWidget* InventoryItemSlot = CreateWidget<UInventoryItemSlotWidget>(this, ItemSlotClass);
		InventoryItemSlot->SetItemInfo(ItemInfos[i]);
		CreateSlotBindings(InventoryItemSlot);
		ItemSlots.Add(InventoryItemSlot);

		ItemGrid->AddChild(InventoryItemSlot);
		if (UUniformGridSlot* GridSlot = Cast<UUniformGridSlot>(InventoryItemSlot->Slot))
		{
			GridSlot->SetColumn((i) % SlotsInRow);
			GridSlot->SetRow((i) / SlotsInRow);
		}
	}
}


void UPlayerInventoryWidget::CreateSlotBindings(UInventoryToolSlotWidget* ToolSlotWidget)
{
	ToolSlotWidget->OnClicked.AddDynamic(this, &UPlayerInventoryWidget::OnToolSlotClicked);
	ToolSlotWidget->OnHovered.AddDynamic(this, &UPlayerInventoryWidget::OnToolSlotHovered);
	ToolSlotWidget->OnUnhovered.AddDynamic(this, &UPlayerInventoryWidget::OnSlotUnhovered);
}

void UPlayerInventoryWidget::CreateSlotBindings(UInventoryItemSlotWidget* ItemSlotWidget)
{
	ItemSlotWidget->OnClicked.AddDynamic(this, &UPlayerInventoryWidget::OnItemSlotClicked);
	ItemSlotWidget->OnHovered.AddDynamic(this, &UPlayerInventoryWidget::OnItemSlotHovered);
	ItemSlotWidget->OnUnhovered.AddDynamic(this, &UPlayerInventoryWidget::OnSlotUnhovered);
}

void UPlayerInventoryWidget::OnToolSlotClicked(UInventorySlotWidget* ClickedSlot)
{
	if (!ActiveSlot)
	{
		ActiveSlot = ClickedSlot;
	}
	else
	{
		if (UInventoryToolSlotWidget* ActiveToolSlot = Cast<UInventoryToolSlotWidget>(ActiveSlot))
		{
			if (UInventoryToolSlotWidget* ClickedToolSlot = Cast<UInventoryToolSlotWidget>(ClickedSlot))
			{
				FToolInfo ActiveToolInfo = ActiveToolSlot->GetToolInfo();
				FToolInfo ClickedToolInfo = ClickedToolSlot->GetToolInfo();
				ActiveToolSlot->SetToolInfo(ClickedToolInfo);
				ClickedToolSlot->SetToolInfo(ActiveToolInfo);
				OnToolSlotHovered(ClickedSlot);
				ActiveSlot = nullptr;
			}
			else
			{
				ActiveSlot = ClickedSlot;
			}
		}
		else
		{
			ActiveSlot = ClickedSlot;
		}
	}
}

void UPlayerInventoryWidget::OnItemSlotClicked(UInventorySlotWidget* ClickedSlot)
{
	if (!ActiveSlot)
	{
		ActiveSlot = ClickedSlot;
	}
	else
	{
		if (UInventoryItemSlotWidget* ActiveItemSlot = Cast<UInventoryItemSlotWidget>(ActiveSlot))
		{
			if (UInventoryItemSlotWidget* ClickedItemSlot = Cast<UInventoryItemSlotWidget>(ClickedSlot))
			{
				FItemInfo ActiveItemInfo = ActiveItemSlot->GetItemInfo();
				FItemInfo ClickedItemInfo = ClickedItemSlot->GetItemInfo();
				ActiveItemSlot->SetItemInfo(ClickedItemInfo);
				ClickedItemSlot->SetItemInfo(ActiveItemInfo);
				OnItemSlotHovered(ClickedSlot);
				ActiveSlot = nullptr;
			}
			else
			{
				ActiveSlot = ClickedSlot;
			}
		}
		else
		{
			ActiveSlot = ClickedSlot;
		}
	}
}

void UPlayerInventoryWidget::OnToolSlotHovered(UInventorySlotWidget* HoveredSlot)
{
	if (UInventoryToolSlotWidget* ToolSlot = Cast<UInventoryToolSlotWidget>(HoveredSlot))
	{
		if (DescriptionBox)
		{
			FToolInfo ToolInfo = ToolSlot->GetToolInfo();
			DescriptionBox->SetText(ToolInfo.Name, ToolInfo.Description);
		}
	}
}

void UPlayerInventoryWidget::OnItemSlotHovered(UInventorySlotWidget* HoveredSlot)
{
	if (UInventoryItemSlotWidget* ItemSlot = Cast<UInventoryItemSlotWidget>(HoveredSlot))
	{
		if (DescriptionBox)
		{
			FItemInfo ItemInfo = ItemSlot->GetItemInfo();
			DescriptionBox->SetText(ItemInfo.Name, ItemInfo.Description);
		}
	}
}

void UPlayerInventoryWidget::OnSlotUnhovered()
{
	if (DescriptionBox)
	{
		DescriptionBox->ClearText();
	}
}

void UPlayerInventoryWidget::CloseWidget()
{
	UpdatePlayerInventory();
	RestoreGame();
	RemoveFromParent();
}

void UPlayerInventoryWidget::UpdatePlayerInventory()
{
	if (!PlayerRef)
	{
		return;
	}

	TArray<FToolInfo> ToolInfos;
	ToolInfos.Add(CurrentToolSlot->GetToolInfo());
	for (UInventoryToolSlotWidget* ToolSlot : ToolSlots)
	{
		ToolInfos.Add(ToolSlot->GetToolInfo());
	}

	TArray<FItemInfo> ItemInfos;
	for (UInventoryItemSlotWidget* ItemSlot : ItemSlots)
	{
		ItemInfos.Add(ItemSlot->GetItemInfo());
	}

	PlayerRef->UpdateToolInventory(ToolInfos);
	PlayerRef->UpdateItemInventory(CurrentItemSlot->GetItemInfo(), ItemInfos);
}

void UPlayerInventoryWidget::RestoreGame()
{
	if (AFarmingGameMode* GameMode = Cast<AFarmingGameMode>(GetWorld()->GetAuthGameMode()))
	{
		GameMode->RestoreGame();
	}
}