// The Green Heart @Politechnika Opolska

#include "InventorySlotWidget.h"
#include "Components/Image.h"

#include "Widgets/Buttons/FocusButton.h"

bool UInventorySlotWidget::Initialize()
{
	bool b = Super::Initialize();
	Button->OnClicked.AddDynamic(this, &UInventorySlotWidget::OnButtonClicked);
	Button->OnHovered.AddDynamic(this, &UInventorySlotWidget::OnButtonHovered);
	Button->OnUnhovered.AddDynamic(this, &UInventorySlotWidget::OnButtonUnhovered);
	Button->StartUpdating();
	return b;
}

void UInventorySlotWidget::SetupFocus()
{
	Button->SetKeyboardFocus();
}

void UInventorySlotWidget::OnButtonClicked()
{
	OnClicked.Broadcast(this);
}

void UInventorySlotWidget::OnButtonHovered()
{
	SetupFocus();
	OnHovered.Broadcast(this);
}

void UInventorySlotWidget::OnButtonUnhovered()
{
	OnUnhovered.Broadcast();
}

void UInventorySlotWidget::SetThumbnail(UTexture2D* NewTexture)
{
	Thumbnail->SetBrushFromTexture(NewTexture);
}

void UInventorySlotWidget::Select()
{
	Button->Select();
}

void UInventorySlotWidget::Deselect()
{
	Button->Deselect();
}