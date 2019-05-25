#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "FocusButton.generated.h"

UENUM(BlueprintType)
enum class EFocusButtonState : uint8
{
	MouseHovered,
	KeyboardHovered,
	Unhovered
};

UCLASS()
class GREENHEART_API UFocusButton : public UButton
{
	GENERATED_BODY()
	
public:
	void StartUpdating();

	void Select();

	void Deselect();

protected:
	UPROPERTY(EditDefaultsOnly, Category="Setup")
	FButtonStyle SelectedStyle;

	FButtonStyle MouseStyle;

	FButtonStyle KeyboardFocusedStyle;

	FButtonStyle KeyboardUnfocusedStyle;

	FButtonStyle SelectedMouseStyle;

	FButtonStyle SelectedKeyboardFocusedStyle;

	FButtonStyle SelectedKeyboardUnfocusedStyle;


private:
	UFUNCTION()
	void UpdateFocus();

	void UpdateStyle(bool bForce);

	EFocusButtonState GetCurrentState();

	float UpdateRate = 0.1f;

	FTimerHandle UpdateTimer;

	EFocusButtonState LastState = EFocusButtonState::Unhovered;

	bool bSelected = false;
};
