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
	GetWorld()->GetTimerManager().SetTimer(UpdateTimer, this, &UFocusButton::UpdateFocus, UpdateRate, true, 0.0f);
}

void UFocusButton::UpdateFocus()
{
	if (IsHovered())
	{
		SetStyle(MouseStyle);
	}
	else
	{
		if (HasKeyboardFocus())
		{
			SetStyle(KeyboardFocusedStyle);
		}
		else
		{
			SetStyle(KeyboardUnfocusedStyle);
		}
	}
}