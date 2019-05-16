// The Green Heart @Politechnika Opolska

#include "BaseAnimalItem.h"

int32 ABaseAnimalItem::GetPrice()
{
	return SellPrice;
}

int32 ABaseAnimalItem::GetEnergyPoints()
{
	return EnergyPoints;
}

UAnimMontage* ABaseAnimalItem::GetConsumeMontage()
{
	return ConsumeMontage;
}