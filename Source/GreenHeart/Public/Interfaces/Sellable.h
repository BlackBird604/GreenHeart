// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Sellable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class USellable : public UInterface
{
	GENERATED_BODY()
};


class GREENHEART_API ISellable
{
	GENERATED_BODY()

public:
	virtual int32 GetPrice() = 0;

};
