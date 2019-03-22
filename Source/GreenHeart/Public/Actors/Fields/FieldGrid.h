// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FieldGrid.generated.h"

class AFieldTile;

UCLASS()
class GREENHEART_API AFieldGrid : public AActor
{
	GENERATED_BODY()
	
public:	
	AFieldGrid();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Setup")
	FVector2D TileSpacing = FVector2D(100, 100);

	UPROPERTY(EditAnywhere, Category = "Setup")
	FVector2D TileAmount = FVector2D(3, 3);

	UPROPERTY(EditDefaultsOnly, Category = "Classes")
	TSubclassOf<class AFieldTile> TileClass;

private:
	void SpawnFieldTiles();

	FVector GetTileSpawnLocation(int32 Row, int32 Column) const;

	UPROPERTY()
	TArray<AFieldTile*> TileActors;
};
