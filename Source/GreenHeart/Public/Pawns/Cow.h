// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "Pawns/Animal.h"
#include "Actors/Others/BaseItem.h"
#include "Interfaces/Collectable.h"
#include "Cow.generated.h"

class ABaseItem;

UCLASS()
class GREENHEART_API ACow : public AAnimal, public ICollectable
{
	GENERATED_BODY()

public:
	virtual void RestoreStateByID(int32 AnimalID) override;

	virtual void UseTool(const ATool* Instigator, int32 Strength = 0) override;

	virtual bool CanBeCollected() override;

	virtual AActor* Collect() override;

	virtual UAnimMontage* GetPickupMontage() override;

protected:
	virtual void SaveUpdatedState() override;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	UAnimMontage* PickupMontage;
};
