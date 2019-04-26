// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "Structs/ItemInventoryState.h"
#include "Components/ActorComponent.h"
#include "ItemInventoryComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GREENHEART_API UItemInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UItemInventoryComponent();

protected:
	virtual void BeginPlay() override;

public:
	FItemInventoryState GetState();

	void RestoreState(FItemInventoryState ItemState);

	bool HasPlace();

	void AddItem(FItemInfo ItemInfo);

	AActor* TakeOut();

	void Update(TArray<FItemInfo> NewItemInfos);

private:
	AActor* SpawnItem(FItemInfo ItemInfo);

	void RestoreSize(int32 Level);

	void RestoreItems(const TArray<FItemInfo>& SavedItemInfos);

	TArray<FItemInfo> ItemInfos;

	int32 CurrentLevel;
};
