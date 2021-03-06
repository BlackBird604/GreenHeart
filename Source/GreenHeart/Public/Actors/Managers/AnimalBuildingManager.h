// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "Actors/Others/DeferrableActor.h"
#include "Structs/AnimalBuildingState.h"
#include "Enums/AnimalTypes.h"
#include "AnimalBuildingManager.generated.h"

class AAnimal;
class UBoxComponent;
class AAnimalSpawnPoint;

UCLASS()
class GREENHEART_API AAnimalBuildingManager : public ADeferrableActor
{
	GENERATED_BODY()
	
public:
	AAnimalBuildingManager();

protected:
	virtual void StartPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

protected:
	virtual FAnimalBuildingState GetSavedBuildingState() { return FAnimalBuildingState(); };

	virtual void SaveState(const FAnimalBuildingState& CurrentBuildingState) {};

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AAnimal> AnimalClass;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	EAnimalType AnimalType;

private:
	void RestoreFeedBoxState(const FAnimalBuildingState& BuildingState);

	void InitializeSpawnPoints();

	void SpawnAnimals();

	FRotator GetRandomSpawnRotation();

	FAnimalBuildingState GetCurrentBuildingState();

	TArray<AAnimalSpawnPoint*> SpawnPoints;
};
