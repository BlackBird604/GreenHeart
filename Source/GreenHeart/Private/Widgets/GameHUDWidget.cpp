// The Green Heart @Politechnika Opolska

#include "GameHUDWidget.h"
#include "Widgets/ClockWidget.h"

void UGameHUDWidget::UpdateClock(const FClockInfo& ClockInfo)
{
	if (ClockWidget)
	{
		ClockWidget->SetClockText(ClockInfo);
	}
}

void UGameHUDWidget::UpdateMoney(const int32 NewAmount)
{
	if (ClockWidget)
	{
		ClockWidget->SetMoneyText(NewAmount);
	}
}