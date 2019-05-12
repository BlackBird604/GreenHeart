// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DestroyActor.generated.h"

class USkeletalMeshComponent;
class UAnimSequence;

UCLASS()
class GREENHEART_API ADestroyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ADestroyActor();

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(VisibleAnywhere, Category = "Setup")
	USkeletalMeshComponent* Mesh;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	UAnimSequence* DestroyAnimation;

private:
	UFUNCTION()
	void OnAnimationEnd();

	FTimerHandle AnimationTimer;
};
