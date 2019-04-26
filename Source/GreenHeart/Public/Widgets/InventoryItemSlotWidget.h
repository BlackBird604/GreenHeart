// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "Structs/ItemInfo.h"
#include "Widgets/InventorySlotWidget.h"
#include "InventoryItemSlotWidget.generated.h"

UCLASS()
class GREENHEART_API UInventoryItemSlotWidget : public UInventorySlotWidget
{
	GENERATED_BODY()
	
public:
	void SetItemInfo(const FItemInfo& NewItemInfo);

	FItemInfo GetItemInfo();

private:
	FItemInfo ItemInfo;
};
