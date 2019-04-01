// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ToolAffectable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UToolAffectable : public UInterface
{
	GENERATED_BODY()
};


class ATool;

class GREENHEART_API IToolAffectable
{
	GENERATED_BODY()

public:
	virtual void UseTool(const ATool* Instigator) = 0;
};
