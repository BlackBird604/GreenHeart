// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Structs/ItemInfo.h"
#include "PickupItem.generated.h"

UINTERFACE(MinimalAPI)
class UPickupItem : public UInterface
{
	GENERATED_BODY()
};


class GREENHEART_API IPickupItem
{
	GENERATED_BODY()

public:
	virtual bool CanBeStored() = 0;

	virtual FItemInfo GetItemInfo() = 0;
};
