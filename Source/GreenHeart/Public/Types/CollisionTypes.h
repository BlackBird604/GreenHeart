#pragma once

#define ECC_ToolTrace			ECC_GameTraceChannel1
#define ECC_InteractionTrace	ECC_GameTraceChannel2
#define ECC_ObstacleTrace		ECC_GameTraceChannel3

namespace CollisionPresets
{
	const FName Plant("Plant");
	const FName Field("Field");
	const FName Obstacle("Obstacle");
	const FName Throwable("Throwable");
	const FName Interactable("Interactable");
	const FName Pawn("Pawn");
}