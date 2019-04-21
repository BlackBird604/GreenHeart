// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "Actors/Tools/Tool.h"
#include "Actors/Fields/Plant.h"
#include "Seeds.generated.h"


UCLASS()
class GREENHEART_API ASeeds : public ATool
{
	GENERATED_BODY()
	
public:
	ASeeds();

	TSubclassOf<APlant> GetPlantClass() const;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<APlant> PlantClass;
};
