// The Green Heart @Politechnika Opolska

#include "ToolInventoryComponent.h"
#include "Actors/Tools/Tool.h"

UToolInventoryComponent::UToolInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	while (ToolInfos.Num() < MinimumSize)
	{
		ToolInfos.Push(FToolInfo());
	}
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

void UToolInventoryComponent::RestoreState(FToolInventoryState InventoryState)
{
	ToolInfos = InventoryState.ToolInfos;
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

	if (CurrentTool.Class)
	{
		UE_LOG(LogTemp, Warning, TEXT("Current tool: %s"), *CurrentTool.Class->GetDisplayNameText().ToString()) // TEMPORARY
	}
}

FToolInfo UToolInventoryComponent::GetCurrentTool()
{
	return ToolInfos[0];
}

void UToolInventoryComponent::RemoveCurrentTool()
{
	ToolInfos[0] = FToolInfo();
}

