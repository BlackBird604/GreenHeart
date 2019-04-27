// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "Actors/Managers/ManagerBase.h"
#include "Structs/AnimalBuildingState.h"
#include "Enums/AnimalTypes.h"
#include "AnimalBuildingManager.generated.h"

class AAnimal;
class UBoxComponent;

UCLASS()
class GREENHEART_API AAnimalBuildingManager : public AManagerBase
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

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UBoxComponent* SpawnBox;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AAnimal> AnimalClass;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	EAnimalType AnimalType;

private:
	void RestoreFeedBoxState(const FAnimalBuildingState& BuildingState);

	void SpawnAnimals();

	FVector GetRandomSpawnLocation();

	FRotator GetRandomSpawnRotation();

	FAnimalBuildingState GetCurrentBuildingState();

};
