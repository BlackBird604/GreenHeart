// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventorySlotWidget.generated.h"


class UButton;
class UImage;


UCLASS()
class GREENHEART_API UInventorySlotWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetThumbnail(UTexture2D* NewThumbnail);

protected:
	UPROPERTY(meta = (BindWidget))
	UButton* Button;

	UPROPERTY(meta = (BindWidget))
	UImage* Thumbnail;

};

