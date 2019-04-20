// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ItemInteractable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UItemInteractable : public UInterface
{
	GENERATED_BODY()
};

class AActor;

class GREENHEART_API IItemInteractable
{
	GENERATED_BODY()

public:
	virtual bool CanInteract(AActor* Item) = 0;

	virtual void Interact(AActor* Item) = 0;
};
