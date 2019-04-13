// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Crop.generated.h"

class USphereComponent;
class UStaticMeshComponent;

UCLASS()
class GREENHEART_API ACrop : public AActor
{
	GENERATED_BODY()
	
public:	
	ACrop();

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* CollisionSphere;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* CropMesh;
};
