// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "Structs/ToolInfo.h"
#include "Widgets/InventorySlotWidget.h"
#include "InventoryToolSlotWidget.generated.h"

UCLASS()
class GREENHEART_API UInventoryToolSlotWidget : public UInventorySlotWidget
{
	GENERATED_BODY()
	
public:
	void SetToolInfo(const FToolInfo& NewToolInfo);

	FToolInfo GetToolInfo();

private:
	FToolInfo ToolInfo;
};
