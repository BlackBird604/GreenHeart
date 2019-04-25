// The Green Heart @Politechnika Opolska

#include "InventorySlotWidget.h"
#include "Components/Image.h"
#include "Components/Button.h"

bool UInventorySlotWidget::Initialize()
{
	bool b = Super::Initialize();
	Button->OnUnhovered.AddDynamic(this, &UInventorySlotWidget::OnButtonUnhovered);
	return b;
}

void UInventorySlotWidget::OnButtonUnhovered()
{
	OnUnhovered.Broadcast();
}

void UInventorySlotWidget::SetThumbnail(UTexture2D* NewTexture)
{
	Thumbnail->SetBrushFromTexture(NewTexture);
}