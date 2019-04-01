// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Plant.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
class UStaticMesh;

USTRUCT(BlueprintType)
struct FGrowthInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 GrowthValue = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMesh* PlantMesh;
};

UCLASS()
class GREENHEART_API APlant : public AActor
{
	GENERATED_BODY()
	
public:	
	APlant();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UBoxComponent* CollisionBox;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* PlantMesh;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TArray<FGrowthInfo> GrowthInfos;

	int32 GrowthValue = 0;
};
