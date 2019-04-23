// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "Actors/Managers/ManagerBase.h"
#include "BarnManager.generated.h"

class UBoxComponent;
class AAnimal;

UCLASS()
class GREENHEART_API ABarnManager : public AManagerBase
{
	GENERATED_BODY()
	
public:	
	ABarnManager();

protected:
	virtual void StartPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UBoxComponent* SpawnBox;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AAnimal> AnimalClass;

private:
	void RestoreState();

	void SpawnAnimals();

	FVector GetRandomSpawnLocation();

	FRotator GetRandomSpawnRotation();

	void SaveState();
};