// The Green Heart @Politechnika Opolska

#include "StartMenuWidget.h"

#include "Widgets/Buttons/FocusButton.h"
#include "Fundamentals/FarmingGameInstance.h"


bool UStartMenuWidget::Initialize()
{
	bool b = Super::Initialize();
	SetupButtonBindings();
	NewGameButton->StartUpdating();
	QuitButton->StartUpdating();
	return b;
}

void UStartMenuWidget::SetupButtonBindings()
{
	NewGameButton->OnClicked.AddDynamic(this, &UStartMenuWidget::StartNewGame);
	QuitButton->OnClicked.AddDynamic(this, &UStartMenuWidget::QuitGame);
}

void UStartMenuWidget::InitializeFocus()
{
	NewGameButton->SetKeyboardFocus();
}

void UStartMenuWidget::StartNewGame()
{
	if (UFarmingGameInstance* GameInstance = GetGameInstance<UFarmingGameInstance>())
	{
		GameInstance->StartNewGame();
	}
}

void UStartMenuWidget::QuitGame()
{
	GetWorld()->GetFirstPlayerController()->ConsoleCommand("quit");
}