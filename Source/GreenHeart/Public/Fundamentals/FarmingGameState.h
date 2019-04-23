// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Structs/GameStateInfo.h"
#include "Structs/ResourceInfo.h"
#include "FarmingGameState.generated.h"


UCLASS()
class GREENHEART_API AFarmingGameState : public AGameStateBase
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	void AddCow();

	int32 GetCowAmount();

	FAnimalState GetCowStateByID(int32 ID);

	void UpdateCowState(FAnimalState NewState);
	
	void AddChcicken();
	
private:
	TArray<FAnimalState> CowStates;

	TArray<FAnimalState> ChickenStates;
};
