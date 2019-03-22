// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FieldTile.generated.h"

class UBoxComponent;
class UDecalComponent;

UCLASS()
class GREENHEART_API AFieldTile : public AActor
{
	GENERATED_BODY()
	
public:	
	AFieldTile();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UBoxComponent* CollisionBox;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UDecalComponent* Decal;

private:
	bool bIsWatered = false;

	bool bIsTilled = false;
};
