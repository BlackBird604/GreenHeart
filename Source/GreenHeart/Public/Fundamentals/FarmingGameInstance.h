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
class USoundWave;

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

	void SetBackgroundMusicTime(float NewTime);

	float GetBackgroundMusicTime();

	int32 GetSpawnPointIndex();

	void StartNextDay();

	void InitializeVariables();

	void StartNewGame();

private:
	void SetupFarmerInventory(FFarmerState& FarmerState);

	void SetupStationaryInventories(FGameStateInfo& GameState);

	FName GetLevelNameWithSuffix(FName LevelName);

	FName GetLevelNameWithSuffix(FName Prefix, EConstructionType ConstructionType);

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	UDataTable* InitialObstacleStates;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	FFarmerState InitialFarmerState;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TArray<TSubclassOf<class ATool>> InitialToolClasses;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TArray<TSubclassOf<class ATool>> InitialStationaryToolClasses;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 StationaryToolInventorySize = 8;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 StationaryItemInventorySize = 8;

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

	float BackgroundMusicTime = 0.0f;
};
