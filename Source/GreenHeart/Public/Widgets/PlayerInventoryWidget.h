// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Structs/FarmerState.h"
#include "PlayerInventoryWidget.generated.h"

class UUniformGridPanel;
class UInventoryItemSlotWidget;
class UInventoryToolSlotWidget;
class UDescriptionWidget;


UCLASS()
class GREENHEART_API UPlayerInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void PopulateSlots(const FFarmerState& FarmerState);

protected:
	UPROPERTY(meta = (BindWidget))
	UInventoryToolSlotWidget* CurrentToolSlot;

	UPROPERTY(meta = (BindWidget))
	UInventoryItemSlotWidget* CurrentItemSlot;

	UPROPERTY(meta = (BindWidget))
	UUniformGridPanel* ToolGrid;

	UPROPERTY(meta = (BindWidget))
	UUniformGridPanel* ItemGrid;

	UPROPERTY(meta = (BindWidget))
	UDescriptionWidget* DescriptionBox;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<UInventoryToolSlotWidget> ToolSlotClass;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<UInventoryItemSlotWidget> ItemSlotClass;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 SlotsInRow = 1;

private:
	void PopulateToolSlots(const TArray<FToolInfo>& ToolInfos);

	void PopulateItemSlots(const FItemInfo& ItemInHands, const TArray<FItemInfo>& ToolInfos);

	void BindHoverFuntions(UInventoryToolSlotWidget* ToolSlotWidget);

	void BindHoverFuntions(UInventoryItemSlotWidget* ItemSlotWidget);

	UFUNCTION()
	void OnToolSlotHovered(const FToolInfo& ToolInfo);

	UFUNCTION()
	void OnItemSlotHovered(const FItemInfo& ToolInfo);

	UFUNCTION()
	void OnSlotUnhovered();
};
