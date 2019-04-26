// The Green Heart @Politechnika Opolska

#include "PlayerInventoryWidget.h"
#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"

#include "Widgets/InventoryToolSlotWidget.h"
#include "Widgets/InventoryItemSlotWidget.h"
#include "Widgets/DescriptionWidget.h"

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
	if (ToolInfos.Num() == 0)
	{
		return;
	}

	CurrentToolSlot->SetToolInfo(ToolInfos[0]);
	BindHoverFuntions(CurrentToolSlot);

	for (int i = 1; i < ToolInfos.Num(); i++)
	{
		UInventoryToolSlotWidget* InventoryToolSlot = CreateWidget<UInventoryToolSlotWidget>(this, ToolSlotClass);
		InventoryToolSlot->SetToolInfo(ToolInfos[i]);
		BindHoverFuntions(InventoryToolSlot);

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
	BindHoverFuntions(CurrentItemSlot);

	for (int i = 0; i < ItemInfos.Num(); i++)
	{
		UInventoryItemSlotWidget* InventoryItemSlot = CreateWidget<UInventoryItemSlotWidget>(this, ItemSlotClass);
		InventoryItemSlot->SetItemInfo(ItemInfos[i]);
		BindHoverFuntions(InventoryItemSlot);

		ItemGrid->AddChild(InventoryItemSlot);
		if (UUniformGridSlot* GridSlot = Cast<UUniformGridSlot>(InventoryItemSlot->Slot))
		{
			GridSlot->SetColumn((i) % SlotsInRow);
			GridSlot->SetRow((i) / SlotsInRow);
		}
	}
}

void UPlayerInventoryWidget::BindHoverFuntions(UInventoryToolSlotWidget* ToolSlotWidget)
{
	ToolSlotWidget->OnHovered.AddDynamic(this, &UPlayerInventoryWidget::OnToolSlotHovered);
	ToolSlotWidget->OnUnhovered.AddDynamic(this, &UPlayerInventoryWidget::OnSlotUnhovered);
}

void UPlayerInventoryWidget::BindHoverFuntions(UInventoryItemSlotWidget* ItemSlotWidget)
{
	ItemSlotWidget->OnHovered.AddDynamic(this, &UPlayerInventoryWidget::OnItemSlotHovered);
	ItemSlotWidget->OnUnhovered.AddDynamic(this, &UPlayerInventoryWidget::OnSlotUnhovered);
}

void UPlayerInventoryWidget::OnToolSlotHovered(const FToolInfo& ToolInfo)
{
	if (DescriptionBox)
	{
		DescriptionBox->SetText(ToolInfo.Name, ToolInfo.Description);
	}
}

void UPlayerInventoryWidget::OnItemSlotHovered(const FItemInfo& ItemInfo)
{
	if (DescriptionBox)
	{
		DescriptionBox->SetText(ItemInfo.Name, ItemInfo.Description);
	}
}

void UPlayerInventoryWidget::OnSlotUnhovered()
{
	if (DescriptionBox)
	{
		DescriptionBox->ClearText();
	}
}