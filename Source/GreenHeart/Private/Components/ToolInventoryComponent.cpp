// The Green Heart @Politechnika Opolska

#include "ToolInventoryComponent.h"
#include "Actors/Tools/Tool.h"

UToolInventoryComponent::UToolInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UToolInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
}

FToolInventoryState UToolInventoryComponent::GetState()
{
	return InventoryState;
}

void UToolInventoryComponent::RestoreState(FToolInventoryState SavedInventoryState)
{
	InventoryState = SavedInventoryState;
	RestoreSize(InventoryState.Level);
}

void UToolInventoryComponent::RestoreSize(int32 Level)
{
	int32 NewSize = FMath::Pow(2, Level+1) + 1;
	InventoryState.ToolInfos.SetNum(NewSize);
}

void UToolInventoryComponent::NextTool()
{
	for (int32 i = InventoryState.ToolInfos.Num() - 1; i >= 0; i--)
	{
		if (InventoryState.ToolInfos[i].Class)
		{
			FToolInfo NextTool = InventoryState.ToolInfos[i];
			InventoryState.ToolInfos.RemoveAt(i);
			InventoryState.ToolInfos.Insert(NextTool, 0);
			break;
		}
	}

	FToolInfo CurrentTool = InventoryState.ToolInfos[0];
}

FToolInfo UToolInventoryComponent::GetCurrentTool()
{
	if (InventoryState.ToolInfos.Num() > 0)
	{
		return InventoryState.ToolInfos[0];
	}
	return FToolInfo();
}

void UToolInventoryComponent::RemoveCurrentTool()
{
	if (InventoryState.ToolInfos.Num() > 0)
	{
		InventoryState.ToolInfos[0] = FToolInfo();
	}
}

void UToolInventoryComponent::Update(TArray<FToolInfo> NewToolInfos)
{
	int32 ToolsToUpdate = FMath::Min(NewToolInfos.Num(), InventoryState.ToolInfos.Num());
	for (int32 i = 0; i < ToolsToUpdate; i++)
	{
		InventoryState.ToolInfos[i] = NewToolInfos[i];
	}
}

bool UToolInventoryComponent::HasPlace()
{
	for (FToolInfo ToolInfo : InventoryState.ToolInfos)
	{
		if (!ToolInfo.Class)
		{
			return true;
		}
	}
	return false;
}

void UToolInventoryComponent::InsertNewTool(const FToolInfo& NewToolInfo)
{
	for (int32 i = 0; i < InventoryState.ToolInfos.Num(); i++)
	{
		if (!InventoryState.ToolInfos[i].Class)
		{
			InventoryState.ToolInfos[i] = NewToolInfo;
			return;
		}
	}
}