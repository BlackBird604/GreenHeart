// The Green Heart @Politechnika Opolska

#include "PauseWidget.h"
#include "Engine/World.h"

#include "Widgets/Buttons/FocusButton.h"
#include "Fundamentals/FarmingGameMode.h"

bool UPauseWidget::Initialize()
{
	bool b = Super::Initialize();
	bStopAction = true;
	FOnInputAction Callback;
	Callback.BindUFunction(this, FName("CloseWidget"));
	ListenForInputAction("Pause", EInputEvent::IE_Pressed, false, Callback);

	ContinueButton->OnClicked.AddDynamic(this, &UPauseWidget::ContinueGame);
	QuitButton->OnClicked.AddDynamic(this, &UPauseWidget::QuitGame);
	return b;
}

void UPauseWidget::SetupFocus()
{
	ContinueButton->SetKeyboardFocus();
}

void UPauseWidget::ContinueGame()
{
	CloseWidget();
}

void UPauseWidget::QuitGame()
{
	if (AFarmingGameMode* GameMode = GetWorld()->GetAuthGameMode<AFarmingGameMode>())
	{
		GetWorld()->GetFirstPlayerController()->ConsoleCommand("quit");
	}
}

void UPauseWidget::CloseWidget()
{
	if (AFarmingGameMode* GameMode = GetWorld()->GetAuthGameMode<AFarmingGameMode>())
	{
		GameMode->Unpause();
	}
	RemoveFromParent();
}