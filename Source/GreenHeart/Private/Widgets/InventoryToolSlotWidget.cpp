// The Green Heart @Politechnika Opolska

#include "InventoryToolSlotWidget.h"
#include "Components/Button.h"

void UInventoryToolSlotWidget::SetToolInfo(const FToolInfo& NewToolInfo)
{
	ToolInfo = NewToolInfo;
	SetThumbnail(ToolInfo.Thumbnail);
}

FToolInfo UInventoryToolSlotWidget::GetToolInfo()
{
	return ToolInfo;
}
