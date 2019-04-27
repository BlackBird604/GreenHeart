// The Green Heart @Politechnika Opolska

#include "InventoryToolSlotWidget.h"
#include "Components/Button.h"

void UInventoryToolSlotWidget::SetToolInfo(const FToolInfo& NewToolInfo)
{
	ToolInfo = NewToolInfo;
	FLevelInfo ToolLevelInfo = ToolInfo.GetCurrentLevelInfo();
	SetThumbnail(ToolLevelInfo.Thumbnail);
}

FToolInfo UInventoryToolSlotWidget::GetToolInfo()
{
	return ToolInfo;
}
