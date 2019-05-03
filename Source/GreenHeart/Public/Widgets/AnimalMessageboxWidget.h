// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AnimalMessageboxWidget.generated.h"


UCLASS()
class GREENHEART_API UAnimalMessageboxWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintImplementableEvent)
	void PlayPositiveAnimation();

	UFUNCTION(BlueprintImplementableEvent)
	void PlayNegativeAnimation();
};
