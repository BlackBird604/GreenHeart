// The Green Heart @Politechnika Opolska

#include "PlayerInventoryWidget.h"
#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"

#include "Widgets/InventorySlotWidget.h"

void UPlayerInventoryWidget::PopulateSlots(const FFarmerState& FarmerState)
{
	const TArray<FToolInfo>& ToolInfos = FarmerState.ToolInventoryState.ToolInfos;
	const TArray<FItemInfo>& ItemInfos = FarmerState.ItemInventoryState.ItemInfos;
	const FItemInfo& ItemInHands = FarmerState.ItemInHandsInfo;

	PopulateToolSlots(ToolInfos);
	PopulateItemSlots(ItemInHands, ItemInfos);
}

void UPlayerInventoryWidget::PopulateToolSlots(const TArray<FToolInfo>& ToolInfos)
{
	if (ToolInfos.Num() <= 0)
	{
		return;
	}

	CurrentToolSlot->SetThumbnail(ToolInfos[0].Thumbnail);

	for (int i = 1; i < ToolInfos.Num(); i++)
	{
		UInventorySlotWidget* InventorySlot = CreateWidget<UInventorySlotWidget>(this, SlotClass);
		InventorySlot->SetThumbnail(ToolInfos[i].Thumbnail);
		ToolGrid->AddChild(InventorySlot);
		if (UUniformGridSlot* GridSlot = Cast<UUniformGridSlot>(InventorySlot->Slot))
		{
			GridSlot->SetColumn((i-1) % SlotsInRow);
			GridSlot->SetRow((i-1) / SlotsInRow);
		}
	}
}

void UPlayerInventoryWidget::PopulateItemSlots(const FItemInfo& ItemInHands, const TArray<FItemInfo>& ItemInfos)
{
	if (ItemInfos.Num() <= 0)
	{
		return;
	}

	CurrentItemSlot->SetThumbnail(ItemInHands.Thumbnail);

	for (int i = 0; i < ItemInfos.Num(); i++)
	{
		UInventorySlotWidget* InventorySlot = CreateWidget<UInventorySlotWidget>(this, SlotClass);
		InventorySlot->SetThumbnail(ItemInfos[i].Thumbnail);
		ItemGrid->AddChild(InventorySlot);
		if (UUniformGridSlot* GridSlot = Cast<UUniformGridSlot>(InventorySlot->Slot))
		{
			GridSlot->SetColumn((i) % SlotsInRow);
			GridSlot->SetRow((i) / SlotsInRow);
		}
	}
}