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
class ADestroyActor;

USTRUCT(BlueprintType)
struct FGrowthInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 GrowthValue = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMesh* PlantMesh;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDepletedSignature);

UCLASS()
class GREENHEART_API APlant : public AActor, public IToolAffectable, public ICollectable
{
	GENERATED_BODY()
	

public:	
	APlant();

protected:
	virtual void BeginPlay() override;


public:
	virtual void UseTool(const ATool* Instigator, int32 Strength) override;

	virtual bool CanBeCollected() override;

	virtual AActor* Collect() override;

	virtual UAnimMontage* GetPickupMontage() override;

	FPlantState GetState();

	void RestoreState(const FPlantState& PlantState);

	int32 GetMaxGrowthValue();

	bool HasMesh(int32 CheckedValue);

	UPROPERTY(BlueprintAssignable)
	FOnDepletedSignature OnDepleted;

protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UBoxComponent* CollisionBox;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* PlantMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TArray<FGrowthInfo> GrowthInfos;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<ACrop> CropClass;

	UPROPERTY(EditDefaultsOnly, Category = "Setup", meta = (ClampMin = "1"))
	int32 NumberOfCollections = 1;

	UPROPERTY(EditDefaultsOnly, Category = "Setup", meta = (ClampMin = "0"))
	int32 GrowthValueAfterCollecting = 0;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	UAnimMontage* PickupMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<ADestroyActor> DestroyActorClass;

private:
	void UpdateMesh();

	void HandleDestroy();

	void SpawnDestroyActor();

	int32 GrowthValue = 0;
};
