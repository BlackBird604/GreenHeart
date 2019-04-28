// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Structs/ConstructionState.h"
#include "ConstructionUpdater.generated.h"


UCLASS()
class GREENHEART_API UConstructionUpdater : public UObject
{
	GENERATED_BODY()
	
public:
	void ApplyNextDay(TArray<FConstructionState>& ConstructionStates);

};
