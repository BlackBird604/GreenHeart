// The Green Heart @Politechnika Opolska

#include "FocusButton.h"
#include "Engine/World.h"
#include "TimerManager.h"

void UFocusButton::StartUpdating()
{
	MouseStyle = WidgetStyle;
	KeyboardFocusedStyle = WidgetStyle;
	KeyboardFocusedStyle.Normal = WidgetStyle.Hovered;
	KeyboardUnfocusedStyle = WidgetStyle;
	KeyboardUnfocusedStyle.Hovered = WidgetStyle.Normal;

	SelectedMouseStyle = SelectedStyle;
	SelectedKeyboardFocusedStyle = SelectedStyle;
	SelectedKeyboardFocusedStyle.Normal = SelectedStyle.Hovered;
	SelectedKeyboardUnfocusedStyle = SelectedStyle;
	SelectedKeyboardUnfocusedStyle.Hovered = SelectedStyle.Normal;
	GetWorld()->GetTimerManager().SetTimer(UpdateTimer, this, &UFocusButton::UpdateFocus, UpdateRate, true, 0.0f);
}

void UFocusButton::UpdateFocus()
{
	UpdateStyle(false);
}

void UFocusButton::UpdateStyle(bool bForce)
{
	EFocusButtonState CurrentState = GetCurrentState();
	if (CurrentState == LastState && !bForce)
	{
		return;
	}

	switch (CurrentState)
	{
	case EFocusButtonState::MouseHovered:
		SetStyle(bSelected ? SelectedMouseStyle : MouseStyle);
		break;
	case EFocusButtonState::KeyboardHovered:
		if (LastState != EFocusButtonState::MouseHovered || bForce)
		{
			SetStyle(bSelected ? SelectedKeyboardFocusedStyle : KeyboardFocusedStyle);
			OnHovered.Broadcast();
		}
		break;
	case EFocusButtonState::Unhovered:
		SetStyle(bSelected ? SelectedKeyboardUnfocusedStyle : KeyboardUnfocusedStyle);
		break;
	}
	LastState = CurrentState;
}

EFocusButtonState UFocusButton::GetCurrentState()
{
	if (IsHovered())
	{
		return EFocusButtonState::MouseHovered;
	}
	if (HasKeyboardFocus())
	{
		return EFocusButtonState::KeyboardHovered;
	}
	return EFocusButtonState::Unhovered;
}

void UFocusButton::Select()
{
	bSelected = true;
	UpdateStyle(true);
}

void UFocusButton::Deselect()
{
	bSelected = false;
	UpdateStyle(true);
}