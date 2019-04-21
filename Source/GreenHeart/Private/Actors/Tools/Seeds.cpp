// The Green Heart @Politechnika Opolska

#include "Seeds.h"

ASeeds::ASeeds()
{
	bIsSingleUse = true;
}

TSubclassOf<APlant> ASeeds::GetPlantClass() const
{
	return PlantClass;
}