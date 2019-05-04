#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "FocusButton.generated.h"


UCLASS()
class GREENHEART_API UFocusButton : public UButton
{
	GENERATED_BODY()
	
public:
	void StartUpdating();

protected:
	FButtonStyle MouseStyle;

	FButtonStyle KeyboardFocusedStyle;

	FButtonStyle KeyboardUnfocusedStyle;

private:
	UFUNCTION()
	void UpdateFocus();

	float UpdateRate = 0.1f;

	FTimerHandle UpdateTimer;
};
