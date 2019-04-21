// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "Actors/Others/BaseItem.h"
#include "Feed.generated.h"

UCLASS()
class GREENHEART_API AFeed : public ABaseItem
{
	GENERATED_BODY()
	
public:	
	AFeed();

protected:
	virtual void BeginPlay() override;

};
