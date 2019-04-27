// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Structs/FieldGridState.h"
#include "Structs/ObstacleState.h"
#include "Structs/FarmerState.h"
#include "Structs/AnimalBuildingState.h"
#include "Structs/GameStateInfo.h"
#include "FarmingGameInstance.generated.h"

class UDataTable;

UCLASS()
class GREENHEART_API UFarmingGameInstance : public UGameInstance
{
	GENERATED_BODY()

protected:
	virtual void Init() override;

public:
	void ApplyNextDayChanges();

	void SetGridState(FFieldGridState NewState);

	FFieldGridState GetGridState();

	void SetObstacleStates(TArray<FObstacleState> NewObstacleStates);

	TArray<FObstacleState> GetObstacleStates();

	void SetFarmerState(FFarmerState NewState);

	FFarmerState GetFarmerState();

	void SetBarnState(FAnimalBuildingState NewState);

	FAnimalBuildingState GetBarnState();

	void SetCoopState(FAnimalBuildingState NewState);

	FAnimalBuildingState GetCoopState();

	void SetGameStateInfo(FGameStateInfo NewState);

	FGameStateInfo GetGameStateInfo();

	void OpenLevel(FName LevelName, int32 SpawnPoint);

	int32 GetSpawnPointIndex();

	void StartNextDay();

private:
	void StartNewGame();

	void SetupFarmerInventory(FFarmerState& FarmerState);

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	UDataTable* InitialObstacleStates;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	FFarmerState InitialFarmerState;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TArray<TSubclassOf<class ATool>> InitialToolClasses;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	FGameStateInfo InitialGameStateInfo;

	UPROPERTY()
	FFieldGridState FieldGridState;

	UPROPERTY()
	TArray<FObstacleState> ObstacleStates;

	UPROPERTY()
	FFarmerState FarmerState;

	UPROPERTY()
	FAnimalBuildingState BarnState;

	UPROPERTY()
	FAnimalBuildingState CoopState;

	FGameStateInfo GameStateInfo;

	int32 SpawnPointIndex = 0;
};
