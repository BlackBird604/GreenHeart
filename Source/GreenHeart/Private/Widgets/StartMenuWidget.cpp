// The Green Heart @Politechnika Opolska

#include "StartMenuWidget.h"
#include "Components/Button.h"

#include "Fundamentals/FarmingGameInstance.h"


bool UStartMenuWidget::Initialize()
{
	bool b = Super::Initialize();
	SetupButtonBindings();
	return b;
}

void UStartMenuWidget::SetupButtonBindings()
{
	NewGameButton->OnClicked.AddDynamic(this, &UStartMenuWidget::StartNewGame);
	QuitButton->OnClicked.AddDynamic(this, &UStartMenuWidget::QuitGame);
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