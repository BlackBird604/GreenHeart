// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/Interactable.h"
#include "MerchantStand.generated.h"

UCLASS()
class GREENHEART_API AMerchantStand : public AActor, public IInteractable
{
	GENERATED_BODY()

public:
	AMerchantStand();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Interact() override;
};