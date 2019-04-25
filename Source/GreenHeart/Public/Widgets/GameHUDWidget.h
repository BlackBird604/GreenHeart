// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Structs/ClockInfo.h"
#include "GameHUDWidget.generated.h"

class UClockWidget;

UCLASS()
class GREENHEART_API UGameHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void UpdateClock(const FClockInfo& ClockInfo);

protected:
	UPROPERTY(meta = (BindWidget))
	UClockWidget* ClockWidget;
};
