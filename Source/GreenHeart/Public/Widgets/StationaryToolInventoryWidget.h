// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Structs/ToolInfo.h"
#include "StationaryToolInventoryWidget.generated.h"

class UUniformGridPanel;
class UInventoryToolSlotWidget;
class UDescriptionWidget;
class AFarmer;

UCLASS()
class GREENHEART_API UStationaryToolInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual bool Initialize() override;

	void PopulateSlots(AFarmer* Farmer, const TArray<FToolInfo>& StoredTools);

protected:
	UPROPERTY(meta = (BindWidget))
	UInventoryToolSlotWidget* CurrentToolSlot;

	UPROPERTY(meta = (BindWidget))
	UUniformGridPanel* EquippedToolGrid;

	UPROPERTY(meta = (BindWidget))
	UUniformGridPanel* StoredToolGrid;

	UPROPERTY(meta = (BindWidget))
	UDescriptionWidget* DescriptionBox;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<UInventoryToolSlotWidget> ToolSlotClass;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 SlotsInRow = 1;

private:
	void PopulateEquippedToolSlots(const TArray<FToolInfo>& ToolInfos);

	void PopulateStoredToolSlots(const TArray<FToolInfo>& ToolInfos);

	UInventoryToolSlotWidget* GenerateToolSlot(UUniformGridPanel* GridPanel, const FToolInfo& ToolInfo, int32 Index);

	void CreateSlotBindings(UInventoryToolSlotWidget* ToolSlotWidget);

	UFUNCTION()
	void OnToolSlotClicked(UInventorySlotWidget* ClickedSlot);

	UFUNCTION()
	void OnToolSlotHovered(UInventorySlotWidget* HoveredSlot);

	UFUNCTION()
	void OnSlotUnhovered();

	UFUNCTION()
	void CloseWidget();

	void UpdatePlayerInventory();

	void UpdateStationaryInventory();

	void RestoreGame();

	TArray<UInventoryToolSlotWidget*> EquippedToolSlots;

	TArray<UInventoryToolSlotWidget*> StoredToolSlots;

	UInventorySlotWidget* ActiveSlot = nullptr;

	AFarmer* PlayerRef;
	
};
