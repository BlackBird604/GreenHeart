// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enums/ToolTypes.h"
#include "Interfaces/ToolAffectable.h"
#include "Obstacle.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
class ADestroyActor;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDestroyedSignature, AActor*, DestroyedActor);

UCLASS()
class GREENHEART_API AObstacle : public AActor, public IToolAffectable
{
	GENERATED_BODY()
	
public:	
	AObstacle();

protected:
	virtual void BeginPlay() override;

public:
	virtual void UseTool(const ATool* Instigator, int32 Strength) override;

	UPROPERTY(BlueprintAssignable)
	FOnDestroyedSignature OnObstacleDestroyed;

protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UBoxComponent* CollisionBox;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* ObstacleMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	EToolType AffectedByTool;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 HealthPoints = 1;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 RequiredStrength = 1;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<ADestroyActor> DestroyActorClass;

private:
	void ApplyDamage(int32 Strength);

	void SpawnDestroyActor();
};
