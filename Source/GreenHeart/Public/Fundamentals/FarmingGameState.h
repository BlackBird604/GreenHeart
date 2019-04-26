// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Structs/GameStateInfo.h"
#include "Enums/StationaryInventoryTypes.h"
#include "FarmingGameState.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMoneyChangedSignature);

UCLASS()
class GREENHEART_API AFarmingGameState : public AGameStateBase
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	FOnMoneyChangedSignature OnMoneyChanged;

	void AddCow();

	int32 GetCowAmount();

	FAnimalState GetCowStateByID(int32 ID);

	void UpdateCowState(FAnimalState NewState);
	
	void AddChcicken();

	int32 GetChickenAmount();

	FAnimalState GetChickenStateByID(int32 ID);

	void UpdateChickenState(FAnimalState NewState);

	int32 GetResourceAmount(EResourceType ResourceType);

	void AddResource(EResourceType ResourceType, int32 Amount);

	void RemoveResource(EResourceType ResourceType, int32 Amount);

	FClockInfo GetClockInfo();

	void  SetClockInfo(FClockInfo NewClockInfo);

	void SetStationaryInventoryInfo(const TArray<FToolInfo>& NewToolInfos);

	void SetStationaryInventoryInfo(const TArray<FItemInfo>& NewItemInfos);

	TArray<FToolInfo> GetStationaryToolInventoryInfo();

	TArray<FItemInfo> GetStationaryItemInventoryInfo();

private:
	void SetResourceAmount(EResourceType ResourceType, int32 Amount);

	TArray<FAnimalState> CowStates;

	TArray<FAnimalState> ChickenStates;

	TMap<EResourceType, FResourceInfo> ResourceInfos;

	FClockInfo ClockInfo;

	TArray<FToolInfo> StationaryTools;

	TArray<FItemInfo> StationaryItems;
};
