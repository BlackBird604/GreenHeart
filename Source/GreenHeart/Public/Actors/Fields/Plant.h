// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/ToolAffectable.h"
#include "Interfaces/Collectable.h"
#include "Structs/PlantState.h"
#include "Plant.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
class UStaticMesh;
class ACrop;

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
class GREENHEART_API APlant : public AActor, public IToolAffectable, public ICollectable
{
	GENERATED_BODY()
	

public:	
	APlant();

protected:
	virtual void BeginPlay() override;


public:
	virtual void UseTool(const ATool* Instigator) override;

	virtual bool CanBeCollected() override;

	virtual TSubclassOf<AActor> Collect() override;

	FPlantState GetState();

	void RestoreState(const FPlantState& PlantState);

	int32 GetMaxGrowthValue();

	bool HasMesh(int32 CheckedValue);

protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UBoxComponent* CollisionBox;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* PlantMesh;

private:
	void UpdateMesh();

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TArray<FGrowthInfo> GrowthInfos;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<ACrop> CropClass;

	int32 GrowthValue = 0;
};
