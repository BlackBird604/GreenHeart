// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/Throwable.h"
#include "Interfaces/PickupItem.h"
#include "Structs/ItemInfo.h"
#include "BaseItem.generated.h"

class USphereComponent;
class UStaticMeshComponent;
class UProjectileMovementComponent;

UCLASS()
class GREENHEART_API ABaseItem : public AActor, public IThrowable, public IPickupItem
{
	GENERATED_BODY()
	
public:	
	ABaseItem();

protected:
	virtual void BeginPlay() override;

public:
	virtual bool CanBeThrown(const FVector& Direction) override;

	virtual void Throw(const FVector& Direction) override;

	virtual bool CanBeStored() override;

	virtual FItemInfo GetItemInfo() override;

protected:
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* CollisionSphere;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* ItemMesh;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UProjectileMovementComponent* ProjectileMovement;

private:
	float HorizontalSpeed = 300.0f;

	float VerticalSpeed = 100.0f;

};
