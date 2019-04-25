// The Green Heart @Politechnika Opolska

#pragma once

#include "ClockInfo.generated.h"

USTRUCT(BlueprintType)
struct FClockInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 Hour;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 Minute;

	FClockInfo(int32 NewHour = 0, int32 NewMinute = 0)
	{
		Hour = NewHour;
		Minute = NewMinute;
	}

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