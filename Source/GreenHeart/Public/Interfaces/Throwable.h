// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Throwable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UThrowable : public UInterface
{
	GENERATED_BODY()
};


class GREENHEART_API IThrowable
{
	GENERATED_BODY()

public:
	virtual bool CanBeThrown(const FVector& Direction) = 0;

	virtual void Throw(const FVector& Direction) = 0;
};
