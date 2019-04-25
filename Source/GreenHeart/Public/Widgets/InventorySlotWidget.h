// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventorySlotWidget.generated.h"


class UButton;
class UImage;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUnhoveredSignature);

UCLASS()
class GREENHEART_API UInventorySlotWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	bool Initialize();

public:
	FOnUnhoveredSignature OnUnhovered;

protected:
	void SetThumbnail(UTexture2D* NewTexture);

	UPROPERTY(meta = (BindWidget))
	UButton* Button;

	UPROPERTY(meta = (BindWidget))
	UImage* Thumbnail;

private:
	UFUNCTION()
	void OnButtonUnhovered();

};

