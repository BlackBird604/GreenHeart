// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/ToolAffectable.h"
#include "Structs/FieldTileState.h"
#include "FieldTile.generated.h"

class UBoxComponent;
class UDecalComponent;
class APlant;
class UMaterialInstance;

UCLASS()
class GREENHEART_API AFieldTile : public AActor, public IToolAffectable
{
	GENERATED_BODY()
	
public:	
	AFieldTile();

	virtual void UseTool(const ATool* Instigator) override;

	FFieldTileState GetState();

	void RestoreState(const FFieldTileState& TileState);

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UBoxComponent* CollisionBox;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UDecalComponent* Decal;

	UPROPERTY(EditDefaultsOnly, Category = "Temporary")
	TSubclassOf<APlant> PlantClass;

	UPROPERTY(EditDefaultsOnly, Category = "Setup|Textures")
	UMaterialInstance* Dry;

	UPROPERTY(EditDefaultsOnly, Category = "Setup|Textures")
	UMaterialInstance* Wet;

	UPROPERTY(EditDefaultsOnly, Category = "Setup|Textures")
	UMaterialInstance* DrySeeded;

	UPROPERTY(EditDefaultsOnly, Category = "Setup|Textures")
	UMaterialInstance* WetSeeded;

private:
	void SpawnPlant();

	void UpdateDecalMaterial();

	UPROPERTY()
	APlant* PlantActor;

	bool bIsWatered = false;

	bool bIsTilled = false;

	bool bIsSeeded = false;
};
