// The Green Heart @Politechnika Opolska

#include "InventoryItemSlotWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"

bool UInventoryItemSlotWidget::Initialize()
{
	bool b = Super::Initialize();
	Button->OnHovered.AddDynamic(this, &UInventoryItemSlotWidget::OnButtonHovered);
	return b;
}

void UInventoryItemSlotWidget::SetItemInfo(const FItemInfo& NewItemInfo)
{
	ItemInfo = NewItemInfo;
	SetThumbnail(ItemInfo.Thumbnail);
}

void UInventoryItemSlotWidget::OnButtonHovered()
{
	OnHovered.Broadcast(ItemInfo);
}