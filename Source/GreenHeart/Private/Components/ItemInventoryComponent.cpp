// The Green Heart @Politechnika Opolska

#include "ItemInventoryComponent.h"
#include "Engine/World.h"
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
	return InventoryState;
}

void UItemInventoryComponent::RestoreState(FItemInventoryState SavedInventoryState)
{
	InventoryState = SavedInventoryState;
	InventoryState.Resize();
}

bool UItemInventoryComponent::HasPlace()
{
	for (int32 i = 0; i < InventoryState.ItemInfos.Num(); i++)
	{
		if (!InventoryState.ItemInfos[i].Class)
		{
			return true;
		}
	}
	return false;
}

void UItemInventoryComponent::AddItem(FItemInfo ItemInfo)
{
	for (int32 i = 0; i < InventoryState.ItemInfos.Num(); i++)
	{
		if (!InventoryState.ItemInfos[i].Class)
		{
			InventoryState.ItemInfos[i] = ItemInfo;
			break;
		}
	}
}

AActor* UItemInventoryComponent::TakeOut()
{
	FItemInfo ItemInfo;
	AActor* SpawnedItem = nullptr;
	for (int32 i = 0; i < InventoryState.ItemInfos.Num(); i++)
	{
		if (InventoryState.ItemInfos[i].Class)
		{
			ItemInfo = InventoryState.ItemInfos[i];
			InventoryState.ItemInfos.RemoveAt(i);
			InventoryState.ItemInfos.Add(FItemInfo());
			SpawnedItem = SpawnItem(ItemInfo);
			break;
		}
	}
	return SpawnedItem;
}

AActor* UItemInventoryComponent::SpawnItem(FItemInfo ItemInfo)
{
	if (!ItemInfo.Class)
	{
		return nullptr;
	}
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	return GetWorld()->SpawnActor<AActor>(ItemInfo.Class, SpawnInfo);
}

void UItemInventoryComponent::Update(TArray<FItemInfo> NewItemInfos)
{
	int32 ItemsToUpdate = FMath::Min(NewItemInfos.Num(), InventoryState.ItemInfos.Num());
	for (int32 i = 0; i < ItemsToUpdate; i++)
	{
		InventoryState.ItemInfos[i] = NewItemInfos[i];
	}
}

void UItemInventoryComponent::Upgrade()
{
	InventoryState.Upgrade();
}

bool UItemInventoryComponent::HasItem()
{
	for (int32 i = 0; i < InventoryState.ItemInfos.Num(); i++)
	{
		if (InventoryState.ItemInfos[i].Class)
		{
			return true;
		}
	}
	return false;
}