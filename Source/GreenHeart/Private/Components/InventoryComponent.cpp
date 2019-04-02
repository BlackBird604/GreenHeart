// The Green Heart @Politechnika Opolska

#include "InventoryComponent.h"
#include "Actors/Tools/Tool.h"

UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}


void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UInventoryComponent::NextTool()
{
	TSubclassOf<ATool> CurrentTool = Tools[0];
	Tools.RemoveAt(0);
	Tools.Push(CurrentTool);
	CurrentTool = Tools[0];
	if (CurrentTool)
	{
		UE_LOG(LogTemp, Warning, TEXT("Current tool: %s"), *CurrentTool->GetDisplayNameText().ToString()) // TEMPORARY
	}
}

TSubclassOf<ATool> UInventoryComponent::GetCurrentTool()
{
	return Tools[0];
}

