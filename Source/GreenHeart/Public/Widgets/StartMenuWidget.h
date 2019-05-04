// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StartMenuWidget.generated.h"

class UFocusButton;

UCLASS()
class GREENHEART_API UStartMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual bool Initialize() override;

protected:
	UFUNCTION(BlueprintCallable)
	void InitializeFocus();

	UPROPERTY(meta = (BindWidget))
	UFocusButton* NewGameButton;

	UPROPERTY(meta = (BindWidget))
	UFocusButton* QuitButton;

private:
	UFUNCTION()
	void StartNewGame();

	UFUNCTION()
	void QuitGame();

	void SetupButtonBindings();
};
