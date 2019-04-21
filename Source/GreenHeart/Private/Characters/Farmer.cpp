// The Green Heart @Politechnika Opolska

#include "Farmer.h"
#include "Components/InputComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "Animation/AnimMontage.h"
#include "Animation/AnimInstance.h"

#include "Defaults/ProjectDefaults.h"
#include "Types/CollisionTypes.h"
#include "Actors/Tools/Tool.h"
#include "Components/ToolInventoryComponent.h"
#include "Components/ItemInventoryComponent.h"
#include "Interfaces/Collectable.h"
#include "Interfaces/Throwable.h"
#include "Interfaces/Interactable.h"
#include "Interfaces/PickupItem.h"


AFarmer::AFarmer()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetCapsuleComponent());
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritYaw = false;
	SpringArm->bInheritRoll = false;
	SpringArm->TargetArmLength = 600.0f;
	FRotator SpringArmRotation = FRotator(-40.0f, 45.0f, 0.0f);
	SpringArm->SetRelativeRotation(SpringArmRotation);

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(SpringArm);
	FollowCamera->PostProcessSettings.bOverride_MotionBlurAmount = true;
	FollowCamera->PostProcessSettings.MotionBlurAmount = 0.0f;

	PickupComponent = CreateDefaultSubobject<USceneComponent>(TEXT("PickupComponent"));
	PickupComponent->SetupAttachment(RootComponent);

	ToolInventory = CreateDefaultSubobject<UToolInventoryComponent>(TEXT("ToolInventory"));
	ItemInventory = CreateDefaultSubobject<UItemInventoryComponent>(TEXT("ItemInventory"));

	bUseControllerRotationYaw = false;
	GetMesh()->bReceivesDecals = false;
}

void AFarmer::BeginPlay()
{
	Super::BeginPlay();
	CurrentTool = SpawnTool();
	if (CurrentTool && GetMesh())
	{
		CurrentTool->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("ToolSocket"));
	}
}

void AFarmer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAction("MoveUp", IE_Pressed, this, &AFarmer::OnMoveUpPressed);
	InputComponent->BindAction("MoveDown", IE_Pressed, this, &AFarmer::OnMoveDownPressed);
	InputComponent->BindAction("MoveLeft", IE_Pressed, this, &AFarmer::OnMoveLeftPressed);
	InputComponent->BindAction("MoveRight", IE_Pressed, this, &AFarmer::OnMoveRightPressed);
	InputComponent->BindAction("Sprint", IE_Pressed, this, &AFarmer::OnSprintPressed);

	InputComponent->BindAction("MoveUp", IE_Released, this, &AFarmer::OnMoveUpReleased);
	InputComponent->BindAction("MoveDown", IE_Released, this, &AFarmer::OnMoveDownReleased);
	InputComponent->BindAction("MoveLeft", IE_Released, this, &AFarmer::OnMoveLeftReleased);
	InputComponent->BindAction("MoveRight", IE_Released, this, &AFarmer::OnMoveRightReleased);
	InputComponent->BindAction("Sprint", IE_Released, this, &AFarmer::OnSprintReleased);

	InputComponent->BindAction("UseTool", IE_Pressed, this, &AFarmer::OnUseToolPressed);
	InputComponent->BindAction("UseTool", IE_Released, this, &AFarmer::OnUseToolReleased);
	InputComponent->BindAction("NextTool", IE_Pressed, this, &AFarmer::OnNextToolPressed);
	InputComponent->BindAction("Interact", IE_Pressed, this, &AFarmer::OnInteractPressed);

	InputComponent->BindAction("NextItem", IE_Pressed, this, &AFarmer::OnNextItemPressed);
}

void AFarmer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (ShouldMove())
	{
		FVector MovementDirection = GetActorForwardVector();
		AddMovementInput(MovementDirection);
	}
}

bool AFarmer::ShouldMove()
{
	bool bIsMontagePlaying = IsMontagePlaying();
	bool bHasMovementInputs = MovementInputs.Num() > 0;

	return (!bIsMontagePlaying && (bIsSprinting || bHasMovementInputs));
}

bool AFarmer::IsMontagePlaying()
{
	return GetMesh()->GetAnimInstance()->Montage_IsPlaying(nullptr);
}

void AFarmer::UpdateRotation()
{
	if (MovementInputs.Num() > 0)
	{
		switch (MovementInputs.Last())
		{
		case EMovementDirection::Up:
			SetActorRotation(FRotator(0, 0, 0));
			break;
		case EMovementDirection::Down:
			SetActorRotation(FRotator(0, 180, 0));
			break;
		case EMovementDirection::Left:
			SetActorRotation(FRotator(0, -90, 0));
			break;
		case EMovementDirection::Right:
			SetActorRotation(FRotator(0, 90, 0));
			break;
		}
	}
}

void AFarmer::SetToolHidden(bool bNewHidden)
{
	if (CurrentTool)
	{
		CurrentTool->SetActorHiddenInGame(bNewHidden);
	}
}

void AFarmer::OnMoveUpPressed()
{
	MovementInputs.AddUnique(EMovementDirection::Up);
	UpdateRotation();
}

void AFarmer::OnMoveDownPressed()
{
	MovementInputs.AddUnique(EMovementDirection::Down);
	UpdateRotation();
}

void AFarmer::OnMoveLeftPressed()
{
	MovementInputs.AddUnique(EMovementDirection::Left);
	UpdateRotation();
}

void AFarmer::OnMoveRightPressed()
{
	MovementInputs.AddUnique(EMovementDirection::Right);
	UpdateRotation();
}

void AFarmer::OnSprintPressed()
{
	GetCharacterMovement()->MaxWalkSpeed = 400;
	bIsSprinting = true;
}

void AFarmer::OnMoveUpReleased()
{
	MovementInputs.Remove(EMovementDirection::Up);
	UpdateRotation();
}

void AFarmer::OnMoveDownReleased()
{
	MovementInputs.Remove(EMovementDirection::Down);
	UpdateRotation();
}

void AFarmer::OnMoveLeftReleased()
{
	MovementInputs.Remove(EMovementDirection::Left);
	UpdateRotation();
}

void AFarmer::OnMoveRightReleased()
{
	MovementInputs.Remove(EMovementDirection::Right);
	UpdateRotation();
}

void AFarmer::OnSprintReleased()
{
	GetCharacterMovement()->MaxWalkSpeed = 200;
	bIsSprinting = false;
}

void AFarmer::OnUseToolPressed()
{
	if (IsMontagePlaying() || ItemInHands)
	{
		return;
	}

	bIsUsingTool = true;
	UpdateChargePose();
	GetWorld()->GetTimerManager().SetTimer(ToolChargeTimer, this, &AFarmer::ChargeTool, 1.0f, true, 1.0f);
}

void AFarmer::UpdateChargePose()
{
	if (!CurrentTool)
	{
		return;
	}

	UAnimMontage* ChargeMontage = CurrentTool->GetChargeMontage();
	PlayAnimMontage(ChargeMontage);
}

void AFarmer::ChargeTool()
{
	if (CurrentTool)
	{
		CurrentTool->Charge();
		UpdateChargePose();
	}
}

void AFarmer::OnUseToolReleased()
{
	if (ItemInHands || !bIsUsingTool)
	{
		return;
	}

	GetWorld()->GetTimerManager().ClearTimer(ToolChargeTimer);
	if (CurrentTool)
	{
		UAnimMontage* UseMontage = CurrentTool->GetUseMontage();
		PlayAnimMontage(UseMontage);
		CurrentTool->Use(this);
	}
}

void AFarmer::OnNextToolPressed()
{
	if (IsMontagePlaying())
	{
		return;
	}

	if (CurrentTool)
	{
		CurrentTool->Destroy();
	}

	ToolInventory->NextTool();
	CurrentTool = SpawnTool();
	if (CurrentTool && GetMesh())
	{
		CurrentTool->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("ToolSocket"));
	}
}

void AFarmer::OnNextItemPressed()
{
	if (IsMontagePlaying())
	{
		return;
	}

	if (ItemInHands)
	{
		if (IPickupItem* Item = Cast<IPickupItem>(ItemInHands))
		{
			ItemInventory->AddItem(Item->GetItemInfo());
			ItemInHands->Destroy();
			ItemInHands = nullptr;
		}
	}
	else
	{
		ItemInHands = GetItemFromInventory();
		if (ItemInHands)
		{
			ItemInHands->AttachToComponent(PickupComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		}
	}
}

void AFarmer::OnInteractPressed()
{
	if (IsMontagePlaying())
	{
		return;
	}

	if (IThrowable* ThrowableActor = Cast<IThrowable>(ItemInHands))
	{
		if (ThrowableActor->CanBeThrown(GetActorForwardVector()))
		{
			ThrowableActor->Throw(GetActorForwardVector());
			ItemInHands = nullptr;
			return;
		}
	}

	float TileSize = ProjectDefaults::TileSize;
	float TraceLength = 100.0f;
	FVector TraceStart = GetActorLocation();
	TraceStart += GetActorForwardVector() * TileSize;
	FVector TraceEnd = TraceStart + FVector(0.0f, 0.0f, -TraceLength);

	FHitResult HitResult;
	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_InteractionTrace);
	if (ICollectable* CollectableActor = Cast<ICollectable>(HitResult.Actor))
	{
		if (CollectableActor->CanBeCollected())
		{
			ItemInHands = CollectableActor->Collect();
			if (ItemInHands)
			{
				PlayPickupTimeline();
				ItemInHands->AttachToComponent(PickupComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
			}
		}
	}
	else if (IInteractable* InteractableActor = Cast<IInteractable>(HitResult.Actor))
	{
		InteractableActor->Interact();
	}
}

ATool* AFarmer::SpawnTool()
{
	FToolInfo ToolInfo = ToolInventory->GetCurrentTool();
	if (!ToolInfo.Class)
	{
		return nullptr;
	}
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	return GetWorld()->SpawnActor<ATool>(ToolInfo.Class, SpawnInfo);
}

// TEMPORARY
AActor* AFarmer::GetItemFromInventory()
{
	FItemInfo ItemInfo = ItemInventory->TakeOut();
	if (!ItemInfo.Class)
	{
		return nullptr;
	}
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	return GetWorld()->SpawnActor<AActor>(ItemInfo.Class, SpawnInfo);
}