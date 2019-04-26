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
	FToolInventoryState InventoryState = FToolInventoryState();
	InventoryState.ToolInfos = ToolInfos;
	return InventoryState;
}

void UToolInventoryComponent::RestoreState(FToolInventoryState SavedInventoryState)
{
	CurrentLevel = SavedInventoryState.Level;
	RestoreSize(CurrentLevel);
	RestoreTools(SavedInventoryState.ToolInfos);
}

void UToolInventoryComponent::RestoreSize(int32 Level)
{
	int32 NewSize = FMath::Pow(2, Level) + 1;
	ToolInfos.SetNum(NewSize);
}

void UToolInventoryComponent::RestoreTools(const TArray<FToolInfo>& SavedToolInfos)
{
	int32 ToolsToAdd = FMath::Min(SavedToolInfos.Num(), ToolInfos.Num());
	for (int32 i = 0; i < ToolsToAdd; i++)
	{
		ToolInfos[i] = SavedToolInfos[i];
	}
}

void UToolInventoryComponent::NextTool()
{
	for (int32 i = ToolInfos.Num() - 1; i >= 0; i--)
	{
		if (ToolInfos[i].Class)
		{
			FToolInfo NextTool = ToolInfos[i];
			ToolInfos.RemoveAt(i);
			ToolInfos.Insert(NextTool, 0);
			break;
		}
	}

	FToolInfo CurrentTool = ToolInfos[0];
}

FToolInfo UToolInventoryComponent::GetCurrentTool()
{
	if (ToolInfos.Num() > 0)
	{
		return ToolInfos[0];
	}
	return FToolInfo();
}

void UToolInventoryComponent::RemoveCurrentTool()
{
	if (ToolInfos.Num() > 0)
	{
		ToolInfos[0] = FToolInfo();
	}
}

void UToolInventoryComponent::Update(TArray<FToolInfo> NewToolInfos)
{
	int32 ToolsToUpdate = FMath::Min(NewToolInfos.Num(), ToolInfos.Num());
	for (int32 i = 0; i < ToolsToUpdate; i++)
	{
		ToolInfos[i] = NewToolInfos[i];
	}
}

bool UToolInventoryComponent::HasPlace()
{
	for (FToolInfo ToolInfo : ToolInfos)
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
	for (int32 i = 0; i < ToolInfos.Num(); i++)
	{
		if (!ToolInfos[i].Class)
		{
			ToolInfos[i] = NewToolInfo;
			return;
		}
	}
}