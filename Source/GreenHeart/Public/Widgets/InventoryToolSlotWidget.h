// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "Structs/ToolInfo.h"
#include "Widgets/InventorySlotWidget.h"
#include "InventoryToolSlotWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnToolSlotHoveredSignature, const FToolInfo&, ToolInfo);

UCLASS()
class GREENHEART_API UInventoryToolSlotWidget : public UInventorySlotWidget
{
	GENERATED_BODY()
	
protected:
	bool Initialize();

public:
	FOnToolSlotHoveredSignature OnHovered;

	void SetToolInfo(const FToolInfo& NewToolInfo);

private:
	UFUNCTION()
	void OnButtonHovered();

	FToolInfo ToolInfo;
};
