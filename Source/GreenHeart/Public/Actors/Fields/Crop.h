// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/Throwable.h"
#include "Interfaces/Sellable.h"
#include "Crop.generated.h"

class USphereComponent;
class UStaticMeshComponent;
class UProjectileMovementComponent;

UCLASS()
class GREENHEART_API ACrop : public AActor, public IThrowable, public ISellable
{
	GENERATED_BODY()
	
public:	
	ACrop();

protected:
	virtual void BeginPlay() override;

public:
	virtual bool CanBeThrown(const FVector& Direction) override;

	virtual void Throw(const FVector& Direction) override;

	virtual int32 GetPrice() override;

protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* CollisionSphere;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* CropMesh;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 SellPrice = 0;

private:
	float HorizontalSpeed = 300.0f;

	float VerticalSpeed = 100.0f;
};
