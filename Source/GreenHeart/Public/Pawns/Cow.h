// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "Pawns/Animal.h"
#include "Cow.generated.h"

UCLASS()
class GREENHEART_API ACow : public AAnimal
{
	GENERATED_BODY()

public:
	virtual void RestoreStateByID(int32 AnimalID) override;

private:
	void SaveUpdatedState();

	bool bHasItem = false;
};
