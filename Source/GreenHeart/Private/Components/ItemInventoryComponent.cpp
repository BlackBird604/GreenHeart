// The Green Heart @Politechnika Opolska

#include "ItemInventoryComponent.h"

UItemInventoryComponent::UItemInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UItemInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	
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
