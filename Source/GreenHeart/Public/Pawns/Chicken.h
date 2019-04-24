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

private:
	void SaveUpdatedState();
};
