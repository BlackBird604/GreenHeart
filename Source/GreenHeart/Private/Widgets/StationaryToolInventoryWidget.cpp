// The Green Heart @Politechnika Opolska

#include "StationaryToolInventoryWidget.h"
#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"

#include "Widgets/InventoryToolSlotWidget.h"
#include "Widgets/DescriptionWidget.h"
#include "Fundamentals/FarmingGameMode.h"
#include "Characters/Farmer.h"

bool UStationaryToolInventoryWidget::Initialize()
{
	bool b = Super::Initialize();
	bStopAction = true;
	FOnInputAction Callback;
	Callback.BindUFunction(this, FName("CloseWidget"));
	ListenForInputAction("Interact", EInputEvent::IE_Pressed, false, Callback);
	return b;
}

void UStationaryToolInventoryWidget::PopulateSlots(AFarmer* Farmer, const TArray<FToolInfo>& StoredTools)
{
	PlayerRef = Farmer;
	FFarmerState FarmerState = Farmer->GetCurrentState();
	const TArray<FToolInfo>& EquippedToolInfos = FarmerState.ToolInventoryState.ToolInfos;

	PopulateEquippedToolSlots(EquippedToolInfos);
	PopulateStoredToolSlots(StoredTools);
}

void UStationaryToolInventoryWidget::PopulateEquippedToolSlots(const TArray<FToolInfo>& ToolInfos)
{
	if (ToolInfos.Num() == 0)
	{
		return;
	}

	CurrentToolSlot->SetToolInfo(ToolInfos[0]);
	CreateSlotBindings(CurrentToolSlot);

	for (int i = 1; i < ToolInfos.Num(); i++)
	{
		UInventoryToolSlotWidget* NewToolSlot = GenerateToolSlot(EquippedToolGrid, ToolInfos[i], i-1);
		EquippedToolSlots.Add(NewToolSlot);
	}
}

void UStationaryToolInventoryWidget::PopulateStoredToolSlots(const TArray<FToolInfo>& ToolInfos)
{
	for (int i = 0; i < ToolInfos.Num(); i++)
	{
		UInventoryToolSlotWidget* NewToolSlot = GenerateToolSlot(StoredToolGrid, ToolInfos[i], i);
		StoredToolSlots.Add(NewToolSlot);
	}
}

UInventoryToolSlotWidget* UStationaryToolInventoryWidget::GenerateToolSlot(UUniformGridPanel* GridPanel, const FToolInfo& ToolInfo, int32 Index)
{
	if (!GridPanel)
	{
		return nullptr;
	}

	UInventoryToolSlotWidget* InventoryToolSlot = CreateWidget<UInventoryToolSlotWidget>(this, ToolSlotClass);
	InventoryToolSlot->SetToolInfo(ToolInfo);
	CreateSlotBindings(InventoryToolSlot);

	GridPanel->AddChild(InventoryToolSlot);
	if (UUniformGridSlot* GridSlot = Cast<UUniformGridSlot>(InventoryToolSlot->Slot))
	{
		GridSlot->SetColumn(Index % SlotsInRow);
		GridSlot->SetRow(Index / SlotsInRow);
	}
	return InventoryToolSlot;
}

void UStationaryToolInventoryWidget::CreateSlotBindings(UInventoryToolSlotWidget* ToolSlotWidget)
{
	ToolSlotWidget->OnClicked.AddDynamic(this, &UStationaryToolInventoryWidget::OnToolSlotClicked);
	ToolSlotWidget->OnHovered.AddDynamic(this, &UStationaryToolInventoryWidget::OnToolSlotHovered);
	ToolSlotWidget->OnUnhovered.AddDynamic(this, &UStationaryToolInventoryWidget::OnSlotUnhovered);
}

void UStationaryToolInventoryWidget::OnToolSlotClicked(UInventorySlotWidget* ClickedSlot)
{
	if (!ActiveSlot)
	{
		ActiveSlot = ClickedSlot;
	}
	else
	{
		if (UInventoryToolSlotWidget* ActiveToolSlot = Cast<UInventoryToolSlotWidget>(ActiveSlot))
		{
			if (UInventoryToolSlotWidget* ClickedToolSlot = Cast<UInventoryToolSlotWidget>(ClickedSlot))
			{
				FToolInfo ActiveToolInfo = ActiveToolSlot->GetToolInfo();
				FToolInfo ClickedToolInfo = ClickedToolSlot->GetToolInfo();
				ActiveToolSlot->SetToolInfo(ClickedToolInfo);
				ClickedToolSlot->SetToolInfo(ActiveToolInfo);
				OnToolSlotHovered(ClickedSlot);
				ActiveSlot = nullptr;
			}
			else
			{
				ActiveSlot = ClickedSlot;
			}
		}
		else
		{
			ActiveSlot = ClickedSlot;
		}
	}
}

void UStationaryToolInventoryWidget::OnToolSlotHovered(UInventorySlotWidget* HoveredSlot)
{
	if (UInventoryToolSlotWidget* ToolSlot = Cast<UInventoryToolSlotWidget>(HoveredSlot))
	{
		if (DescriptionBox)
		{
			FToolInfo ToolInfo = ToolSlot->GetToolInfo();
			DescriptionBox->SetText(ToolInfo.Name, ToolInfo.Description);
		}
	}
}

void UStationaryToolInventoryWidget::OnSlotUnhovered()
{
	if (DescriptionBox)
	{
		DescriptionBox->ClearText();
	}
}

void UStationaryToolInventoryWidget::CloseWidget()
{
	UpdatePlayerInventory();
	UpdateStationaryInventory();
	RestoreGame();
	RemoveFromParent();
}

void UStationaryToolInventoryWidget::UpdatePlayerInventory()
{
	if (!PlayerRef)
	{
		return;
	}

	TArray<FToolInfo> ToolInfos;
	ToolInfos.Add(CurrentToolSlot->GetToolInfo());
	for (UInventoryToolSlotWidget* ToolSlot : EquippedToolSlots)
	{
		ToolInfos.Add(ToolSlot->GetToolInfo());
	}

	PlayerRef->UpdateToolInventory(ToolInfos);
}

void UStationaryToolInventoryWidget::UpdateStationaryInventory()
{
	TArray<FToolInfo> ToolInfos;
	for (UInventoryToolSlotWidget* ToolSlot : StoredToolSlots)
	{
		ToolInfos.Add(ToolSlot->GetToolInfo());
	}

	if (AFarmingGameMode* GameMode = Cast<AFarmingGameMode>(GetWorld()->GetAuthGameMode()))
	{
		GameMode->UpdateStationaryInventory(ToolInfos);
	}
}

void UStationaryToolInventoryWidget::RestoreGame()
{
	if (AFarmingGameMode* GameMode = Cast<AFarmingGameMode>(GetWorld()->GetAuthGameMode()))
	{
		GameMode->RestoreGame();
	}
}
