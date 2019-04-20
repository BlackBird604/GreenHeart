// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ObstacleManager.generated.h"

class AObstacle;

UCLASS()
class GREENHEART_API AObstacleManager : public AActor
{
	GENERATED_BODY()
	
public:	
	AObstacleManager();

protected:
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AObstacle> WeedClass;

private:
	UFUNCTION()
	void RemoveObstacle(AActor* RemovedActor);

	void SaveState();

	void RestoreState();

	TArray<AObstacle*> Obstacles;
};
