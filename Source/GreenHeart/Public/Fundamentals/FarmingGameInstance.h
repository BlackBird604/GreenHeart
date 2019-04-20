// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Structs/FieldGridState.h"
#include "Structs/ObstacleState.h"
#include "FarmingGameInstance.generated.h"

class UDataTable;

UCLASS()
class GREENHEART_API UFarmingGameInstance : public UGameInstance
{
	GENERATED_BODY()

protected:
	virtual void Init() override;

public:
	void SetGridState(FFieldGridState NewState);

	FFieldGridState GetGridState();

	void SetObstacleStates(TArray<FObstacleState> NewObstacleStates);

	TArray<FObstacleState> GetObstacleStates();

	void OpenLevel(FName LevelName, int32 SpawnPoint);

	void StartNextDay();

private:
	void StartNewGame();

	void ApplyNextDayChanges();

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	UDataTable* InitialObstacleStates;

	UPROPERTY()
	FFieldGridState FieldGridState;

	UPROPERTY()
	TArray<FObstacleState> ObstacleStates;
};
