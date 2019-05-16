// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Consumable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UConsumable : public UInterface
{
	GENERATED_BODY()
};


class UAnimMontage;

class GREENHEART_API IConsumable
{
	GENERATED_BODY()

public:
	virtual int32 GetEnergyPoints() = 0;

	virtual UAnimMontage* GetConsumeMontage() = 0;
};
