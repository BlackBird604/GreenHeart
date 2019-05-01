// The Green Heart @Politechnika Opolska

#include "StartMenuGameMode.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

#include "Widgets/StartMenuWidget.h"
#include "Fundamentals/FarmingGameInstance.h"

void AStartMenuGameMode::BeginPlay()
{
	Super::BeginPlay();
	UStartMenuWidget* StartMenuWidget = CreateWidget<UStartMenuWidget>(GetWorld(), StartMenuWidgetClass);
	if (StartMenuWidget)
	{
		StartMenuWidget->AddToViewport(1);
		EnableUIMode();
	}
}

void AStartMenuGameMode::EnableUIMode()
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController)
	{
		PlayerController->bShowMouseCursor = true;
		FInputModeGameAndUI InputMode;
		InputMode.SetHideCursorDuringCapture(false);
		PlayerController->SetInputMode(InputMode);
	}
}