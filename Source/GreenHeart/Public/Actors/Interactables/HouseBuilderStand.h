// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "Actors/Interactables/MerchantStand.h"
#include "HouseBuilderStand.generated.h"


UCLASS()
class GREENHEART_API AHouseBuilderStand : public AMerchantStand
{
	GENERATED_BODY()
	
public:
	virtual void StartPlay() override;

	virtual void Interact() override;
};
