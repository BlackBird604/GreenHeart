// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Animal.generated.h"

class UBoxComponent;
class USkeletalMeshComponent;
class UPawnMovementComponent;

UCLASS()
class GREENHEART_API AAnimal : public APawn
{
	GENERATED_BODY()

public:
	AAnimal();

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UBoxComponent* CollisionBox;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USkeletalMeshComponent* AnimalMesh;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UPawnMovementComponent* MovementComponent;

};
