// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StartMenuWidget.generated.h"

class UButton;

UCLASS()
class GREENHEART_API UStartMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual bool Initialize() override;

protected:
	UPROPERTY(meta = (BindWidget))
	UButton* NewGameButton;

	UPROPERTY(meta = (BindWidget))
	UButton* QuitButton;

private:
	UFUNCTION()
	void StartNewGame();

	UFUNCTION()
	void QuitGame();

	void SetupButtonBindings();
};
