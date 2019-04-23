// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Structs/ChickenState.h"
#include "Structs/CowState.h"
#include "Structs/ResourceInfo.h"
#include "FarmingGameState.generated.h"


UCLASS()
class GREENHEART_API AFarmingGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	void AddCow();

	void AddChcicken();

	int32 GetCowAmount();

private:
	TArray<FCowState> CowStates;

	TArray<FChickenState> ChickenStates;
};
