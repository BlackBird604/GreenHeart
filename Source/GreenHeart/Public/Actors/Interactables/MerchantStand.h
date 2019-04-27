// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/Interactable.h"
#include "Enums/MerchantTypes.h"
#include "MerchantStand.generated.h"

class UBoxComponent;
class UStaticMeshComponent;

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

protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UBoxComponent* CollisionBox;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* StandMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	EMerchantType MerchantType;

};