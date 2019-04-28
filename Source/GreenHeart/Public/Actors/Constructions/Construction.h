// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "Actors/Others/DeferrableActor.h"
#include "Enums/ConstructionTypes.h"
#include "Construction.generated.h"


UCLASS()
class GREENHEART_API AConstruction : public ADeferrableActor
{
	GENERATED_BODY()
	
public:
	virtual void StartPlay() override;

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void Initialize(int32 CurrentLevel, bool bIsUnderConstruction);

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	EConstructionType BuildingType;
};
