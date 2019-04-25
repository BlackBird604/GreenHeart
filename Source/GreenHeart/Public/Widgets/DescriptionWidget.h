// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DescriptionWidget.generated.h"

class UTextBlock;

UCLASS()
class GREENHEART_API UDescriptionWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* DescriptionText;
	
};
