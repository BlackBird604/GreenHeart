// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/ToolAffectable.h"
#include "Obstacle.generated.h"

class UBoxComponent;

UCLASS()
class GREENHEART_API AObstacle : public AActor, public IToolAffectable
{
	GENERATED_BODY()
	
public:	
	AObstacle();

protected:
	virtual void BeginPlay() override;

public:
	virtual void UseTool(const ATool* Instigator) override;

protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UBoxComponent* CollisionBox;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* ObstacleMesh;

};
