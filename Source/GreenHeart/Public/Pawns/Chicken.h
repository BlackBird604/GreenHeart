// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "Pawns/Animal.h"
#include "Chicken.generated.h"

UCLASS()
class GREENHEART_API AChicken : public AAnimal
{
	GENERATED_BODY()
	
public:
	virtual void RestoreStateByID(int32 AnimalID) override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float EggSpawnHeight = 0.0f;

	virtual void SaveUpdatedState() override;

private:
	void SpawnEgg();

	UFUNCTION()
	void OnEggCollected();
};
