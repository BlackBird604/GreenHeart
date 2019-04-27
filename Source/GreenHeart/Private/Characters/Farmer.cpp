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
#include "Defaults/GHFuncLib.h"
#include "Types/CollisionTypes.h"
#include "Actors/Tools/Tool.h"
#include "Components/ToolInventoryComponent.h"
#include "Components/ItemInventoryComponent.h"
#include "Interfaces/Collectable.h"
#include "Interfaces/Throwable.h"
#include "Interfaces/Interactable.h"
#include "Interfaces/PickupItem.h"
#include "Interfaces/ItemInteractable.h"
#include "Interfaces/Consumable.h"
#include "Fundamentals/FarmingGameInstance.h"
#include "Fundamentals/FarmingGameMode.h"


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
	RestoreState();

	CurrentTool = SpawnTool();
	if (CurrentTool && GetMesh())
	{
		CurrentTool->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("ToolSocket"));
	}
}

void AFarmer::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	SaveState();
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
	InputComponent->BindAction("Eat", IE_Pressed, this, &AFarmer::OnEatPressed);

	InputComponent->BindAction("ToggleInventory", IE_Pressed, this, &AFarmer::OnToggleInventory);
}

void AFarmer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (ShouldMove())
	{
		UpdateRotation();
		FVector MovementDirection = GetActorForwardVector();
		AddMovementInput(MovementDirection);
	}
}

void AFarmer::SaveState()
{
	UFarmingGameInstance* GameInstance = Cast<UFarmingGameInstance>(GetGameInstance());
	if (GameInstance)
	{
		GameInstance->SetFarmerState(GetCurrentState());
	}
}

FFarmerState AFarmer::GetCurrentState()
{
	FFarmerState FarmerState = FFarmerState();
	FarmerState.ToolInventoryState = ToolInventory->GetState();
	FarmerState.ItemInventoryState = ItemInventory->GetState();
	if (IPickupItem* PickupItem = Cast<IPickupItem>(ItemInHands))
	{
		FarmerState.ItemInHandsInfo = PickupItem->GetItemInfo();
	}
	else
	{
		FarmerState.ItemInHandsInfo = FItemInfo();
	}
	FarmerState.Energy = Energy;
	return FarmerState;
}

void AFarmer::RestoreState()
{
	UFarmingGameInstance* GameInstance = Cast<UFarmingGameInstance>(GetGameInstance());
	if (GameInstance)
	{
		FFarmerState FarmerState = GameInstance->GetFarmerState();
		ToolInventory->RestoreState(FarmerState.ToolInventoryState);
		ItemInventory->RestoreState(FarmerState.ItemInventoryState);
		RestoreItemInHands(FarmerState.ItemInHandsInfo.Class);
		Energy = FarmerState.Energy;
	}
}

bool AFarmer::ShouldMove()
{
	bool bIsMontagePlaying = IsMontagePlaying();
	bool bHasMovementInputs = MovementInputs.Num() > 0;

	return (!bIsMontagePlaying && (bIsSprinting || bHasMovementInputs));
}

void AFarmer::SetSprint(bool bActive)
{
	GetCharacterMovement()->MaxWalkSpeed = bActive ? SprintSpeed : WalkSpeed;
	bIsSprinting = bActive;
}

void AFarmer::UpdateRotation()
{
	if (IsMontagePlaying())
	{
		return;
	}

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

void AFarmer::ClearMovementInput()
{
	MovementInputs.Empty();
	SetSprint(false);
}

bool AFarmer::IsMontagePlaying()
{
	return GetMesh()->GetAnimInstance()->Montage_IsPlaying(nullptr);
}

void AFarmer::SetToolHidden(bool bNewHidden)
{
	if (CurrentTool)
	{
		CurrentTool->SetActorHiddenInGame(bNewHidden);
	}
}

void AFarmer::OnUseToolEnd()
{
	SetToolHidden(true);
	if (CurrentTool && CurrentTool->IsSingleUse())
	{
		ToolInventory->RemoveCurrentTool();
		CurrentTool->Destroy();
		CurrentTool = nullptr;
	}
}

void AFarmer::OnMoveUpPressed()
{
	MovementInputs.AddUnique(EMovementDirection::Up);
}

void AFarmer::OnMoveDownPressed()
{
	MovementInputs.AddUnique(EMovementDirection::Down);
}

void AFarmer::OnMoveLeftPressed()
{
	MovementInputs.AddUnique(EMovementDirection::Left);
}

void AFarmer::OnMoveRightPressed()
{
	MovementInputs.AddUnique(EMovementDirection::Right);
}

void AFarmer::OnSprintPressed()
{
	SetSprint(true);
}

void AFarmer::OnMoveUpReleased()
{
	MovementInputs.Remove(EMovementDirection::Up);
}

void AFarmer::OnMoveDownReleased()
{
	MovementInputs.Remove(EMovementDirection::Down);
}

void AFarmer::OnMoveLeftReleased()
{
	MovementInputs.Remove(EMovementDirection::Left);
}

void AFarmer::OnMoveRightReleased()
{
	MovementInputs.Remove(EMovementDirection::Right);
}

void AFarmer::OnSprintReleased()
{
	SetSprint(false);
}

void AFarmer::OnUseToolPressed()
{
	if (IsMontagePlaying() || ItemInHands)
	{
		return;
	}

	bIsUsingTool = true;
	SetToolHidden(false);
	UpdateChargePose();
	GetWorld()->GetTimerManager().SetTimer(ToolChargeTimer, this, &AFarmer::ChargeTool, 1.0f, true, 1.0f);
}

void AFarmer::OnEatPressed()
{
	if (IsMontagePlaying() || !ItemInHands)
	{
		return;
	}

	if (IConsumable* Consumable = Cast<IConsumable>(ItemInHands))
	{
		Energy += Consumable->GetEnergyPoints();
		DestroyItemInHands();
	}
}

void AFarmer::OnToggleInventory()
{
	if (AFarmingGameMode* GameMode = GetWorld()->GetAuthGameMode<AFarmingGameMode>())
	{
		GameMode->OpenPlayerInventory();
	}
}

void AFarmer::UpdateToolInventory(TArray<FToolInfo> NewToolInfos)
{
	ToolInventory->Update(NewToolInfos);
	UpdateCurrentTool();
}

void AFarmer::UpdateCurrentTool()
{
	if (CurrentTool)
	{
		CurrentTool->Destroy();
	}
	CurrentTool = SpawnTool();
	if (CurrentTool && GetMesh())
	{
		CurrentTool->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("ToolSocket"));
	}
}

void AFarmer::UpdateItemInventory(FItemInfo NewItemInHands, TArray<FItemInfo> NewItemInfos)
{
	DestroyItemInHands();
	RestoreItemInHands(NewItemInHands.Class);
	ItemInventory->Update(NewItemInfos);
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

	bIsUsingTool = false;
	GetWorld()->GetTimerManager().ClearTimer(ToolChargeTimer);
	if (CurrentTool)
	{
		UAnimMontage* UseMontage = CurrentTool->GetUseMontage();
		PlayAnimMontage(UseMontage);
		int32 EnergyDrain = CurrentTool->Use(this);
		Energy -= EnergyDrain;
		UE_LOG(LogTemp, Warning, TEXT("Energy left: %d"), Energy);
	}
}

void AFarmer::OnNextToolPressed()
{
	if (IsMontagePlaying() || ItemInHands)
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
			if (ItemInventory->HasPlace())
			{
				ItemInventory->AddItem(Item->GetItemInfo());
				DestroyItemInHands();
			}
		}
	}
	else
	{
		ItemInHands = ItemInventory->TakeOut();
		if (ItemInHands)
		{
			AttachActorToItemSocket(ItemInHands);
		}
	}
}

void AFarmer::OnInteractPressed()
{
	if (IsMontagePlaying())
	{
		return;
	}

	if (ItemInHands)
	{
		AActor* FoundActor = GetActorByTraceChannel(ECC_InteractionTrace);
		if (IItemInteractable* InteractableActor = Cast<IItemInteractable>(FoundActor))
		{
			if (InteractableActor->CanInteract(ItemInHands))
			{
				InteractableActor->Interact(ItemInHands);
				DestroyItemInHands();
				return;
			}
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
	}

	else
	{
		AActor* FoundActor = GetActorByTraceChannel(ECC_InteractionTrace);
		if (ICollectable* CollectableActor = Cast<ICollectable>(FoundActor))
		{
			if (CollectableActor->CanBeCollected())
			{
				ItemInHands = CollectableActor->Collect();
				if (ItemInHands)
				{
					PlayPickupTimeline();
					AttachActorToItemSocket(ItemInHands);
				}
			}
		}

		else if (IInteractable* InteractableActor = Cast<IInteractable>(FoundActor))
		{
			InteractableActor->Interact();
		}
	}
}

AActor* AFarmer::GetActorByTraceChannel(ECollisionChannel CollisionChannel)
{
	float TileSize = ProjectDefaults::TileSize;
	float TraceLength = 100.0f;
	FVector TraceStart = GetActorLocation();
	TraceStart += GetActorForwardVector() * TileSize;
	FVector TraceEnd = TraceStart + FVector(0.0f, 0.0f, -TraceLength);

	FHitResult HitResult;
	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, CollisionChannel);
	return HitResult.GetActor();
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
	ATool* SpawnedTool = GetWorld()->SpawnActor<ATool>(ToolInfo.Class, SpawnInfo);
	if (SpawnedTool)
	{
		SpawnedTool->Restore(ToolInfo);
	}
	return SpawnedTool;
}

void AFarmer::RestoreItemInHands(TSubclassOf<AActor> ItemClass)
{
	if (!ItemClass)
	{
		return;
	}
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	ItemInHands = GetWorld()->SpawnActor<AActor>(ItemClass, SpawnInfo);
	AttachActorToItemSocket(ItemInHands);
}

void AFarmer::AttachActorToItemSocket(AActor* Item)
{
	if (Item)
	{
		Item->AttachToComponent(PickupComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	}
}

void AFarmer::DestroyItemInHands()
{
	if (ItemInHands)
	{
		ItemInHands->Destroy();
	}
	ItemInHands = nullptr;
}

void AFarmer::AutomaticMoveTo(TArray<FVector> TargetLocations)
{
	for (FVector Location : TargetLocations)
	{
		AutomaticMovementLocations.Add(Location);
	}
	if (!bIsAutomaticMovement)
	{
		StartAutomaticMovement();
	}
}

void AFarmer::AutomaticMoveTo(FVector TargetLocation)
{
	AutomaticMovementLocations.Add(TargetLocation);
	if (!bIsAutomaticMovement)
	{
		StartAutomaticMovement();
	}
}

void AFarmer::MoveToNextPoint()
{
	if (AutomaticMovementLocations.Num() == 0)
	{
		return;
	}
	
	FVector TargetLocation = AutomaticMovementLocations[0];
	AutomaticMovementLocations.RemoveAt(0);

	float XYDistance = UGHFuncLib::XYVectorLength(GetActorLocation(), TargetLocation);
	if (XYDistance == 0.0f)
	{
		OnMovementTimelineFinished();
		return;
	}

	FRotator MovementRotation = GetLookAtXYRotation(TargetLocation);
	SetActorRotation(MovementRotation);

	float Duration = XYDistance / GetCharacterMovement()->MaxWalkSpeed;
	PlayMovementTimeline(Duration);
}

FRotator AFarmer::GetLookAtXYRotation(const FVector& TargetLocation)
{
	FVector ActorLocation = GetActorLocation();
	FVector LookAtVector = TargetLocation - ActorLocation;
	float LookAtYaw = (LookAtVector).Rotation().Yaw;
	FRotator LookAtRotation = GetActorRotation();
	LookAtRotation.Yaw = LookAtYaw;
	return LookAtRotation;
}

void AFarmer::OnMovementTimelineFinished()
{
	if (AutomaticMovementLocations.Num() > 0)
	{
		MoveToNextPoint();
	}
	else
	{
		EndAutomaticMovement();
	}
}

void AFarmer::StartAutomaticMovement()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	DisableInput(PlayerController);
	ClearMovementInput();
	MoveToNextPoint();
}

void AFarmer::EndAutomaticMovement()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	EnableInput(PlayerController);
	bIsAutomaticMovement = false;
}

bool AFarmer::IsToolInventoryFull()
{
	return !ToolInventory->HasPlace();
}

void AFarmer::AddTool(const FToolInfo& NewToolInfo)
{
	ToolInventory->InsertNewTool(NewToolInfo);
	UpdateCurrentTool();
}

void AFarmer::UpgradeToolInventory()
{
	ToolInventory->Upgrade();
}

void AFarmer::UpgradeItemInventory()
{
	ItemInventory->Upgrade();
}