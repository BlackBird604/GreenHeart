// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Structs/FieldGridState.h"
#include "FarmingGameInstance.generated.h"



UCLASS()
class GREENHEART_API UFarmingGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	void SetGridState(FFieldGridState NewState);

	FFieldGridState GetGridState();

	void OpenLevel(FName LevelName, int32 SpawnPoint);

	void StartNextDay();

private:
	void ApplyNextDayChanges();

	UPROPERTY()
	FFieldGridState FieldGridState;
};
