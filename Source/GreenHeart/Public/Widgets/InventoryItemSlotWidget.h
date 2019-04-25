// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "Structs/ItemInfo.h"
#include "Widgets/InventorySlotWidget.h"
#include "InventoryItemSlotWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemSlotHoveredSignature, const FItemInfo&, ItemInfo);

UCLASS()
class GREENHEART_API UInventoryItemSlotWidget : public UInventorySlotWidget
{
	GENERATED_BODY()
	
protected:
	bool Initialize();

public:
	FOnItemSlotHoveredSignature OnHovered;

	void SetItemInfo(const FItemInfo& NewItemInfo);

private:
	UFUNCTION()
	void OnButtonHovered();

	FItemInfo ItemInfo;
};
