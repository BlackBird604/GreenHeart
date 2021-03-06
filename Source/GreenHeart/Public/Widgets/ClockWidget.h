// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Structs/ClockInfo.h"
#include "ClockWidget.generated.h"

class UTextBlock;

UCLASS()
class GREENHEART_API UClockWidget : public UUserWidget
{
	GENERATED_BODY()
	

public:
	void SetClockText(const FClockInfo& NewClockInfo);

	void SetMoneyText(int32 NewAmount);

protected:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* HourText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* MinuteText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* MoneyText;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 DisplayedMinuteIncrements = 1;
};
