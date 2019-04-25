// The Green Heart @Politechnika Opolska

#include "InventorySlotWidget.h"
#include "Components/Image.h"

void UInventorySlotWidget::SetThumbnail(UTexture2D* NewThumbnail)
{
	Thumbnail->SetBrushFromTexture(NewThumbnail);
}