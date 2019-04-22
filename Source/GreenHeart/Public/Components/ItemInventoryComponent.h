// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Structs/ItemInventoryState.h"
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

	void AddItem(FItemInfo ItemInfo);

	FItemInfo TakeOut();

private:
	TArray<FItemInfo> ItemInfos;
};
