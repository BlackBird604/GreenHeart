// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Structs/GameStateInfo.h"
#include "Structs/BarnState.h"
#include "AnimalUpdater.generated.h"


UCLASS()
class GREENHEART_API UAnimalUpdater : public UObject
{
	GENERATED_BODY()
	
public:
	void ApplyNextDay(FGameStateInfo& GameStateInfo, FBarnState& BarnState);

	void UpdateBarn(TArray<FAnimalState>& CowStates, TArray<FFeedBoxState>& FeedBoxStates);

	
};
