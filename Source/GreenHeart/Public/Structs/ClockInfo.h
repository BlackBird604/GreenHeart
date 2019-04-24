// The Green Heart @Politechnika Opolska

#pragma once

#include "ClockInfo.generated.h"

USTRUCT(BlueprintType)
struct FClockInfo
{
	GENERATED_USTRUCT_BODY()

	int32 Hour;

	int32 Minute;

	void AddMinutes(int32 Amount)
	{
		const int32 MinutesInHour = 60;
		const int32 HoursInDay = 24;
		Minute += Amount;
		Hour += Minute / MinutesInHour;
		Hour = Hour % HoursInDay;
		Minute = Minute % MinutesInHour;
	}
};