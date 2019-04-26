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
	FItemInventoryState InventoryState = FItemInventoryState();
	InventoryState.ItemInfos = ItemInfos;
	return InventoryState;
}

void UItemInventoryComponent::RestoreState(FItemInventoryState InventoryState)
{
	RestoreSize(InventoryState.Level);
	RestoreItems(InventoryState.ItemInfos);
}

void UItemInventoryComponent::RestoreSize(int32 Level)
{
	int32 NewSize = FMath::Pow(2, Level);
	ItemInfos.SetNum(NewSize);
}

void UItemInventoryComponent::RestoreItems(const TArray<FItemInfo>& SavedItemInfos)
{
	int32 ItemsToAdd = FMath::Min(SavedItemInfos.Num(), ItemInfos.Num());
	for (int32 i = 0; i < ItemsToAdd; i++)
	{
		ItemInfos[i] = SavedItemInfos[i];
	}
}

bool UItemInventoryComponent::HasPlace()
{
	for (int32 i = 0; i < ItemInfos.Num(); i++)
	{
		if (!ItemInfos[i].Class)
		{
			return true;
		}
	}
	return false;
}

void UItemInventoryComponent::AddItem(FItemInfo ItemInfo)
{
	for (int32 i = 0; i < ItemInfos.Num(); i++)
	{
		if (!ItemInfos[i].Class)
		{
			ItemInfos[i] = ItemInfo;
			break;
		}
	}
}

AActor* UItemInventoryComponent::TakeOut()
{
	FItemInfo ItemInfo;
	AActor* SpawnedItem = nullptr;
	for (int32 i = 0; i < ItemInfos.Num(); i++)
	{
		if (ItemInfos[i].Class)
		{
			ItemInfo = ItemInfos[i];
			ItemInfos.RemoveAt(i);
			ItemInfos.Add(FItemInfo());
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
	int32 ItemsToUpdate = FMath::Min(NewItemInfos.Num(), ItemInfos.Num());
	for (int32 i = 0; i < ItemsToUpdate; i++)
	{
		ItemInfos[i] = NewItemInfos[i];
	}
}