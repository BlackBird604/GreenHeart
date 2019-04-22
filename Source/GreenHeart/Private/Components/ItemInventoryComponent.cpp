// The Green Heart @Politechnika Opolska

#include "ItemInventoryComponent.h"
#include "GameFramework/Actor.h"


UItemInventoryComponent::UItemInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UItemInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

FItemInventoryState UItemInventoryComponent::GetState()
{
	FItemInventoryState InventoryState = FItemInventoryState();
	InventoryState.ItemInfos = ItemInfos;
	return InventoryState;
}

void UItemInventoryComponent::RestoreState(FItemInventoryState InventoryState)
{
	ItemInfos = InventoryState.ItemInfos;
}

void UItemInventoryComponent::AddItem(FItemInfo ItemInfo)
{
	ItemInfos.Add(ItemInfo);
}

// TEMPORARY!
FItemInfo UItemInventoryComponent::TakeOut()
{
	FItemInfo ItemInfo = FItemInfo();
	for (int32 i = 0; i < ItemInfos.Num(); i++)
	{
		if (ItemInfos[i].Class)
		{
			ItemInfo = ItemInfos[i];
			ItemInfos[i] = FItemInfo();
			break;
		}
	}
	return ItemInfo;
}
