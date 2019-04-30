// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Collectable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCollectable : public UInterface
{
	GENERATED_BODY()
};

class AActor;
class UAnimMontage;

class GREENHEART_API ICollectable
{
	GENERATED_BODY()

public:
	virtual bool CanBeCollected() = 0;

	virtual AActor* Collect() = 0;

	virtual UAnimMontage* GetPickupMontage() = 0;
};
