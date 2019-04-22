// The Green Heart @Politechnika Opolska

#include "GHFuncLib.h"

float UGHFuncLib::XYVectorLength(const FVector& A, const FVector& B)
{
	FVector DistanceVector = A - B;
	DistanceVector.Z = 0;
	return DistanceVector.Size();
}