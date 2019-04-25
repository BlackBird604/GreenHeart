// The Green Heart @Politechnika Opolska

#include "ClockWidget.h"
#include "Components/TextBlock.h"

void UClockWidget::SetClockText(const FClockInfo& NewClockInfo)
{
	if (HourText && MinuteText)
	{
		FNumberFormattingOptions Formatting;
		Formatting.SetMinimumIntegralDigits(2);
		FText NewHourText = FText::AsNumber(NewClockInfo.Hour, &Formatting);
		HourText->SetText(NewHourText);

		int32 MinuteValue = NewClockInfo.Minute;
		MinuteValue -= NewClockInfo.Minute % DisplayedMinuteIncrements;
		FText NewMinuteText = FText::AsNumber(MinuteValue, &Formatting);
		MinuteText->SetText(NewMinuteText);
	}
}

void UClockWidget::SetMoneyText(int32 NewAmount)
{
	if (MoneyText)
	{
		FText NewMoneyText = FText::AsNumber(NewAmount);
		MoneyText->SetText(NewMoneyText);
	}
}