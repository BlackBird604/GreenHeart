// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Structs/GameStateInfo.h"
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

	int32 GetResourceAmount(EResourceType ResourceType);

	void AddResource(EResourceType ResourceType, int32 Amount);

	void RemoveResource(EResourceType ResourceType, int32 Amount);

private:
	void SetResourceAmount(EResourceType ResourceType, int32 Amount);

	TArray<FAnimalState> CowStates;

	TArray<FAnimalState> ChickenStates;

	TMap<EResourceType, FResourceInfo> ResourceInfos;
};
