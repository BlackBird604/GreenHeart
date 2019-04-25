// The Green Heart @Politechnika Opolska

#include "InventoryToolSlotWidget.h"
#include "Components/Button.h"

bool UInventoryToolSlotWidget::Initialize()
{
	bool b = Super::Initialize();
	Button->OnHovered.AddDynamic(this, &UInventoryToolSlotWidget::OnButtonHovered);
	return b;
}

void UInventoryToolSlotWidget::SetToolInfo(const FToolInfo& NewToolInfo)
{
	ToolInfo = NewToolInfo;
	SetThumbnail(ToolInfo.Thumbnail);
}

void UInventoryToolSlotWidget::OnButtonHovered()
{
	OnHovered.Broadcast(ToolInfo);
}
