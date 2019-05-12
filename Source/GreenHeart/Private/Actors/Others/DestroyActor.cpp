// The Green Heart @Politechnika Opolska

#include "DestroyActor.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimSequence.h"
#include "TimerManager.h"

ADestroyActor::ADestroyActor()
{
	PrimaryActorTick.bCanEverTick = false;
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
	Mesh->bReceivesDecals = false;
}

void ADestroyActor::BeginPlay()
{
	Super::BeginPlay();
	if (DestroyAnimation)
	{
		Mesh->PlayAnimation(DestroyAnimation, false);
		float AnimationLength = DestroyAnimation->GetPlayLength();
		GetWorldTimerManager().SetTimer(AnimationTimer, this, &ADestroyActor::OnAnimationEnd, AnimationLength);
	}
	else
	{
		Destroy();
	}
}

void ADestroyActor::OnAnimationEnd()
{
	Destroy();
}
