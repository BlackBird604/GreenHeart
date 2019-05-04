// The Green Heart @Politechnika Opolska

#include "StationaryItemInventoryWidget.h"
#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"

#include "Widgets/InventoryItemSlotWidget.h"
#include "Widgets/DescriptionWidget.h"
#include "Fundamentals/FarmingGameMode.h"
#include "Characters/Farmer.h"
#include "Actors/Interactables/StationaryInventory.h"

bool UStationaryItemInventoryWidget::Initialize()
{
	bool b = Super::Initialize();
	bStopAction = true;
	FOnInputAction Callback;
	Callback.BindUFunction(this, FName("CloseWidget"));
	ListenForInputAction("Exit", EInputEvent::IE_Pressed, false, Callback);
	return b;
}

void UStationaryItemInventoryWidget::SetInventoryActor(AActor* NewInventoryActor)
{
	InventoryActor = NewInventoryActor;
}

void UStationaryItemInventoryWidget::PopulateSlots(AFarmer* Farmer, const TArray<FItemInfo>& StoredItems)
{
	PlayerRef = Farmer;
	FFarmerState FarmerState = Farmer->GetCurrentState();
	const FItemInfo& ItemInHands = FarmerState.ItemInHandsInfo;
	const TArray<FItemInfo>& EquippedItemInfos = FarmerState.ItemInventoryState.ItemInfos;

	PopulateEquippedItemSlots(ItemInHands, EquippedItemInfos);
	PopulateStoredItemSlots(StoredItems);
	CurrentItemSlot->SetupFocus();
}

void UStationaryItemInventoryWidget::PopulateEquippedItemSlots(const FItemInfo& ItemInHands, const TArray<FItemInfo>& ItemInfos)
{
	if (ItemInfos.Num() == 0)
	{
		return;
	}

	CurrentItemSlot->SetItemInfo(ItemInHands);
	CreateSlotBindings(CurrentItemSlot);

	for (int i = 0; i < ItemInfos.Num(); i++)
	{
		UInventoryItemSlotWidget* NewItemSlot = GenerateItemSlot(EquippedItemGrid, ItemInfos[i], i);
		EquippedItemSlots.Add(NewItemSlot);
	}
}

void UStationaryItemInventoryWidget::PopulateStoredItemSlots(const TArray<FItemInfo>& ItemInfos)
{
	for (int i = 0; i < ItemInfos.Num(); i++)
	{
		UInventoryItemSlotWidget* NewItemSlot = GenerateItemSlot(StoredItemGrid, ItemInfos[i], i);
		StoredItemSlots.Add(NewItemSlot);
	}
}

UInventoryItemSlotWidget* UStationaryItemInventoryWidget::GenerateItemSlot(UUniformGridPanel* GridPanel, const FItemInfo& ItemInfo, int32 Index)
{
	if (!GridPanel)
	{
		return nullptr;
	}

	UInventoryItemSlotWidget* InventoryItemSlot = CreateWidget<UInventoryItemSlotWidget>(this, ItemSlotClass);
	InventoryItemSlot->SetItemInfo(ItemInfo);
	CreateSlotBindings(InventoryItemSlot);

	GridPanel->AddChild(InventoryItemSlot);
	if (UUniformGridSlot* GridSlot = Cast<UUniformGridSlot>(InventoryItemSlot->Slot))
	{
		GridSlot->SetColumn(Index % SlotsInRow);
		GridSlot->SetRow(Index / SlotsInRow);
	}
	return InventoryItemSlot;
}

void UStationaryItemInventoryWidget::CreateSlotBindings(UInventoryItemSlotWidget* ItemSlotWidget)
{
	ItemSlotWidget->OnClicked.AddDynamic(this, &UStationaryItemInventoryWidget::OnItemSlotClicked);
	ItemSlotWidget->OnHovered.AddDynamic(this, &UStationaryItemInventoryWidget::OnItemSlotHovered);
	ItemSlotWidget->OnUnhovered.AddDynamic(this, &UStationaryItemInventoryWidget::OnSlotUnhovered);
}

void UStationaryItemInventoryWidget::OnItemSlotClicked(UInventorySlotWidget* ClickedSlot)
{
	if (!ActiveSlot)
	{
		ActiveSlot = ClickedSlot;
	}
	else
	{
		if (UInventoryItemSlotWidget* ActiveItemSlot = Cast<UInventoryItemSlotWidget>(ActiveSlot))
		{
			if (UInventoryItemSlotWidget* ClickedItemSlot = Cast<UInventoryItemSlotWidget>(ClickedSlot))
			{
				FItemInfo ActiveItemInfo = ActiveItemSlot->GetItemInfo();
				FItemInfo ClickedItemInfo = ClickedItemSlot->GetItemInfo();
				ActiveItemSlot->SetItemInfo(ClickedItemInfo);
				ClickedItemSlot->SetItemInfo(ActiveItemInfo);
				OnItemSlotHovered(ClickedSlot);
				ActiveSlot = nullptr;
			}
			else
			{
				ActiveSlot = ClickedSlot;
			}
		}
		else
		{
			ActiveSlot = ClickedSlot;
		}
	}
}

void UStationaryItemInventoryWidget::OnItemSlotHovered(UInventorySlotWidget* HoveredSlot)
{
	if (UInventoryItemSlotWidget* ItemSlot = Cast<UInventoryItemSlotWidget>(HoveredSlot))
	{
		if (DescriptionBox)
		{
			FItemInfo ItemInfo = ItemSlot->GetItemInfo();
			DescriptionBox->SetText(ItemInfo.Name, ItemInfo.Description);
		}
	}
}

void UStationaryItemInventoryWidget::OnSlotUnhovered()
{
	if (DescriptionBox)
	{
		DescriptionBox->ClearText();
	}
}

void UStationaryItemInventoryWidget::CloseWidget()
{
	UpdatePlayerInventory();
	UpdateStationaryInventory();
	UpdateInventoryActor();
	RestoreGame();
	RemoveFromParent();
}

void UStationaryItemInventoryWidget::UpdatePlayerInventory()
{
	if (!PlayerRef)
	{
		return;
	}

	TArray<FItemInfo> ItemInfos;
	for (UInventoryItemSlotWidget* ItemSlot : EquippedItemSlots)
	{
		ItemInfos.Add(ItemSlot->GetItemInfo());
	}

	PlayerRef->UpdateItemInventory(CurrentItemSlot->GetItemInfo(), ItemInfos);
}

void UStationaryItemInventoryWidget::UpdateStationaryInventory()
{
	TArray<FItemInfo> ItemInfos;
	for (UInventoryItemSlotWidget* ItemSlot : StoredItemSlots)
	{
		ItemInfos.Add(ItemSlot->GetItemInfo());
	}

	if (AFarmingGameMode* GameMode = Cast<AFarmingGameMode>(GetWorld()->GetAuthGameMode()))
	{
		GameMode->UpdateStationaryInventory(ItemInfos);
	}
}

void UStationaryItemInventoryWidget::UpdateInventoryActor()
{
	if (AStationaryInventory* Inventory = Cast<AStationaryInventory>(InventoryActor))
	{
		Inventory->EndInteraction();
	}
}

void UStationaryItemInventoryWidget::RestoreGame()
{
	if (AFarmingGameMode* GameMode = Cast<AFarmingGameMode>(GetWorld()->GetAuthGameMode()))
	{
		GameMode->RestoreGame();
	}
}
