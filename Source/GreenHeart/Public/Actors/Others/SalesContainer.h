// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enums/ResourceTypes.h"
#include "SalesContainer.generated.h"

class UBoxComponent;
class USkeletalMeshComponent;

UCLASS()
class GREENHEART_API ASalesContainer : public AActor
{
	GENERATED_BODY()
	
public:	
	ASalesContainer();

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UBoxComponent* CollisionBox;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USkeletalMeshComponent* ContainerMesh;

	UFUNCTION()
	void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, 
		AActor* OtherActor, UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
