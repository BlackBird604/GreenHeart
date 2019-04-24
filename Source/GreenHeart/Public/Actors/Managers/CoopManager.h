// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "Actors/Managers/AnimalBuildingManager.h"
#include "CoopManager.generated.h"

UCLASS()
class GREENHEART_API ACoopManager : public AAnimalBuildingManager
{
	GENERATED_BODY()
	
protected:
	virtual FAnimalBuildingState GetSavedBuildingState() override;

	virtual void SaveState(const FAnimalBuildingState& CurrentBuildingState) override;

};
