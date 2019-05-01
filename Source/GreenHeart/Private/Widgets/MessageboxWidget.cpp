// The Green Heart @Politechnika Opolska

#include "MessageboxWidget.h"
#include "Components/TextBlock.h"
#include "TimerManager.h"

bool UMessageboxWidget::Initialize()
{
	bool b = Super::Initialize();
	bStopAction = true;
	FOnInputAction Callback;
	Callback.BindUFunction(this, FName("CloseWidget"));
	ListenForInputAction("Confirm", EInputEvent::IE_Pressed, false, Callback);
	GetWorld()->GetTimerManager().SetTimer(ActivationTimer, this, &UMessageboxWidget::EnableInput, 1.0f, false, 1.0f);
	return b;
}

void UMessageboxWidget::EnableInput()
{
	bInputEnabled = true;
}

void UMessageboxWidget::SetMessage(FText NewMessage)
{
	MessageText->SetText(NewMessage);
}

void UMessageboxWidget::CloseWidget()
{
	if (bInputEnabled)
	{
		OnClosed.Broadcast();
		RemoveFromParent();
	}
}
