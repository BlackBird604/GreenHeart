// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/Interactable.h"
#include "Bed.generated.h"

class UBoxComponent;
class UStaticMeshComponent;

UCLASS()
class GREENHEART_API ABed : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	ABed();

protected:
	virtual void BeginPlay() override;

	virtual void Interact() override;

protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UBoxComponent* CollisionBox;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* BedMesh;

};