// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Structs/LevelInfo.h"
#include "UpgradeConfirmationWidget.generated.h"

class UButton;
class UImage;
class UTextBlock;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUpgradeConfirmedSignature, int32, Price);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUpgradeCanceledSignature);

UCLASS()
class GREENHEART_API UUpgradeConfirmationWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual bool Initialize() override;

	void SetupWidget(const FText& Name, const FLevelInfo& CurrentLevelInfo, const FLevelInfo& NextLevelInfo, int32 CurrentLevel);

	FOnUpgradeConfirmedSignature OnConfirm;

	FOnUpgradeCanceledSignature OnCancel;

protected:
	UPROPERTY(meta = (BindWidget))
	UButton* ConfirmButton;

	UPROPERTY(meta = (BindWidget))
	UButton* CancelButton;

	UPROPERTY(meta = (BindWidget))
	UImage* CurrentLevelThumbnail;

	UPROPERTY(meta = (BindWidget))
	UImage* NextLevelThumbnail;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* NameText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* CurrentLevelText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* NextLevelText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* PriceText;

private:
	UFUNCTION()
	void OnConfirmButtonClicked();

	UFUNCTION()
	void OnCancelButtonClicked();

	void SetLevelText(UTextBlock* TextBlock, int32 Level);

	void SetUpgradePrice(int32 NewPrice);

	int32 Price;
};
