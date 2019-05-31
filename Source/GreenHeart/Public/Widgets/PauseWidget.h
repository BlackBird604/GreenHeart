// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseWidget.generated.h"

class UFocusButton;

UCLASS()
class GREENHEART_API UPauseWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	bool Initialize();

	void SetupFocus();

protected:
	UPROPERTY(meta = (BindWidget))
	UFocusButton* ContinueButton;

	UPROPERTY(meta = (BindWidget))
	UFocusButton* QuitButton;

private:
	UFUNCTION()
	void ContinueGame();

	UFUNCTION()
	void QuitGame();

	UFUNCTION()
	void CloseWidget();
};
