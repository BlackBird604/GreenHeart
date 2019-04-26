// The Green Heart @Politechnika Opolska

#include "InventoryItemSlotWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"

void UInventoryItemSlotWidget::SetItemInfo(const FItemInfo& NewItemInfo)
{
	ItemInfo = NewItemInfo;
	SetThumbnail(ItemInfo.Thumbnail);
}

FItemInfo UInventoryItemSlotWidget::GetItemInfo()
{
	return ItemInfo;
}