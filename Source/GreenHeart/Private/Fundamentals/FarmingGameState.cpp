// The Green Heart @Politechnika Opolska

#include "FarmingGameState.h"
#include "Fundamentals/FarmingGameInstance.h"
#include "Actors/Tools/Tool.h"

void AFarmingGameState::BeginPlay()
{
	Super::BeginPlay();
	if (UFarmingGameInstance* GameInstance = Cast<UFarmingGameInstance>(GetGameInstance()))
	{
		FGameStateInfo SavedState = GameInstance->GetGameStateInfo();
		CowStates = SavedState.CowStates;
		ChickenStates = SavedState.ChickenStates;
		ResourceInfos = SavedState.ResourceInfos;
		ClockInfo = SavedState.ClockInfo;
		StationaryTools = SavedState.StationaryTools;
		StationaryItems = SavedState.StationaryItems;
		BlacksmithInfo = SavedState.BlacksmithInfo;
		SupermarketInfo = SavedState.SupermarketInfo;
		ConstructionStates = SavedState.ConstructionStates;
	}

	for (FConstructionState& State : ConstructionStates)
	{
		UE_LOG(LogTemp,Warning,TEXT("BeginPlay: %s, %d [%d]"), *State.Name.ToString(), State.CurrentLevel, State.ConstructionTimeLeft)
	}
}

void AFarmingGameState::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	if (UFarmingGameInstance* GameInstance = Cast<UFarmingGameInstance>(GetGameInstance()))
	{
		FGameStateInfo GameStateInfo;
		GameStateInfo.CowStates = CowStates;
		GameStateInfo.ChickenStates = ChickenStates;
		GameStateInfo.ResourceInfos = ResourceInfos;
		GameStateInfo.ClockInfo = ClockInfo;
		GameStateInfo.StationaryTools = StationaryTools;
		GameStateInfo.StationaryItems = StationaryItems;
		GameStateInfo.BlacksmithInfo = BlacksmithInfo;
		GameStateInfo.SupermarketInfo = SupermarketInfo;
		GameStateInfo.ConstructionStates = ConstructionStates;
		GameInstance->SetGameStateInfo(GameStateInfo);
	}

	for (FConstructionState& State : ConstructionStates)
	{
		UE_LOG(LogTemp, Warning, TEXT("EndPlay: %s, %d"), *State.Name.ToString(), State.CurrentLevel, State.ConstructionTimeLeft)
	}
}

void AFarmingGameState::AddCow()
{
	FAnimalState AnimalState;
	AnimalState.ID = GetCowAmount();
	CowStates.Add(AnimalState);
}

void AFarmingGameState::AddChcicken()
{
	FAnimalState AnimalState;
	AnimalState.ID = GetChickenAmount();
	ChickenStates.Add(AnimalState);
}

int32 AFarmingGameState::GetCowAmount()
{
	return CowStates.Num();
}

int32 AFarmingGameState::GetChickenAmount()
{
	return ChickenStates.Num();
}

FAnimalState AFarmingGameState::GetCowStateByID(int32 ID)
{
	for (FAnimalState& CowState : CowStates)
	{
		if (CowState.ID == ID)
		{
			return CowState;
		}
	}
	return FAnimalState();
}

FAnimalState AFarmingGameState::GetChickenStateByID(int32 ID)
{
	for (FAnimalState& ChickenState : ChickenStates)
	{
		if (ChickenState.ID == ID)
		{
			return ChickenState;
		}
	}
	return FAnimalState();
}

void AFarmingGameState::UpdateCowState(FAnimalState NewState)
{
	for (int32 i = 0; i < CowStates.Num(); i++)
	{
		if (CowStates[i].ID == NewState.ID)
		{
			CowStates[i] = NewState;
			break;
		}
	}
}

void AFarmingGameState::UpdateChickenState(FAnimalState NewState)
{
	for (int32 i = 0; i < ChickenStates.Num(); i++)
	{
		if (ChickenStates[i].ID == NewState.ID)
		{
			ChickenStates[i] = NewState;
			break;
		}
	}
}

int32 AFarmingGameState::GetResourceAmount(EResourceType ResourceType)
{
	return ResourceInfos.FindRef(ResourceType).Amount;
}

void AFarmingGameState::AddResource(EResourceType ResourceType, int32 Amount)
{
	int32 CurrentAmount = GetResourceAmount(ResourceType);
	int32 NewAmount = CurrentAmount + Amount;
	SetResourceAmount(ResourceType, NewAmount);

	if (ResourceType == EResourceType::Money)
	{
		OnMoneyChanged.Broadcast();
	}
}

void AFarmingGameState::RemoveResource(EResourceType ResourceType, int32 Amount)
{
	AddResource(ResourceType, -Amount);
}

void AFarmingGameState::SetResourceAmount(EResourceType ResourceType, int32 Amount)
{
	FResourceInfo ResourceInfo = ResourceInfos.FindRef(ResourceType);
	ResourceInfo.Amount = Amount;
	ResourceInfos.Add(ResourceType, ResourceInfo);
}

FClockInfo AFarmingGameState::GetClockInfo()
{
	return ClockInfo;
}

void AFarmingGameState::SetClockInfo(FClockInfo NewClockInfo)
{
	ClockInfo = NewClockInfo;
}

void AFarmingGameState::SetStationaryInventoryInfo(const TArray<FToolInfo>& NewToolInfos)
{
	StationaryTools = NewToolInfos;
}

void AFarmingGameState::SetStationaryInventoryInfo(const TArray<FItemInfo>& NewItemInfos)
{
	StationaryItems = NewItemInfos;
}

TArray<FToolInfo> AFarmingGameState::GetStationaryToolInventoryInfo()
{
	return StationaryTools;
}

TArray<FItemInfo> AFarmingGameState::GetStationaryItemInventoryInfo()
{
	return StationaryItems;
}

void AFarmingGameState::SetBlacksmithInfo(const FBlacksmithInfo& NewInfo)
{
	BlacksmithInfo = NewInfo;
}

FBlacksmithInfo AFarmingGameState::GetBlacksmithInfo()
{
	return BlacksmithInfo;
}

FSupermarketInfo AFarmingGameState::GetSupermarketInfo()
{
	return SupermarketInfo;
}

void AFarmingGameState::AddToolToStationaryInventory(const FToolInfo& NewTool)
{
	for (int32 i = 0; i < StationaryTools.Num(); i++)
	{
		if (!StationaryTools[i].Class)
		{
			StationaryTools[i] = NewTool;
			return;
		}
	}
}

TArray<FConstructionState> AFarmingGameState::GetConstructionStates()
{
	return ConstructionStates;
}

FConstructionState AFarmingGameState::GetConstructionState(EConstructionType ConstructionType)
{
	for (FConstructionState State : ConstructionStates)
	{
		if (State.ConstructionType == ConstructionType)
		{
			return State;
		}
	}
	return FConstructionState();
}

void AFarmingGameState::StartConstructionUpgrade(EConstructionType ConstructionType)
{
	for (FConstructionState& State : ConstructionStates)
	{
		if (State.ConstructionType == ConstructionType)
		{
			State.StartUpgrade();
		}
	}
}
