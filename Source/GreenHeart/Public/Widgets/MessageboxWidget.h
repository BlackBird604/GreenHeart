// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MessageboxWidget.generated.h"

class UTextBlock;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMessageBoxClosedSignature);

UCLASS()
class GREENHEART_API UMessageboxWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual bool Initialize() override;

	void SetMessage(FText NewMessage);

	FOnMessageBoxClosedSignature OnClosed;

protected:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* MessageText;

private:
	UFUNCTION()
	void CloseWidget();

	UFUNCTION()
	void EnableInput();

	FTimerHandle ActivationTimer;

	bool bInputEnabled = false;
};
