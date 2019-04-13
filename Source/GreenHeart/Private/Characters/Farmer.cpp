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

#include "Defaults/ProjectDefaults.h"
#include "Types/CollisionTypes.h"
#include "Actors/Tools/Tool.h"
#include "Components/InventoryComponent.h"
#include "Interfaces/Collectable.h"

bool isUpPressed = false;
bool isDownPressed = false;
bool isLeftPressed = false;
bool isRightPressed = false;
bool isSprint = false;
bool doMovement = false;

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

	Inventory = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory"));

	bUseControllerRotationYaw = false;
	GetMesh()->bReceivesDecals = false;
}

void AFarmer::BeginPlay()
{
	Super::BeginPlay();
	CurrentTool = SpawnTool();
}

void AFarmer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Move();
	if (doMovement)
	{
		FVector MovementDirection = GetActorForwardVector();
		AddMovementInput(MovementDirection);
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

	InputComponent->BindAction("ResetLevel", IE_Pressed, this, &AFarmer::OnResetLevelPressed);
	InputComponent->BindAction("NextDay", IE_Pressed, this, &AFarmer::OnNextDayPressed);
}

void AFarmer::Move()
{
	doMovement = true;
	if (isUpPressed && !isDownPressed && !isLeftPressed && !isRightPressed)
		SetActorRotation(FRotator(0, 0, 0));
	else if (isRightPressed && !isLeftPressed && !isUpPressed && !isDownPressed)
		SetActorRotation(FRotator(0, 90, 0));
	else if (isDownPressed && !isUpPressed && !isLeftPressed && !isRightPressed)
		SetActorRotation(FRotator(0, 180, 0));
	else if (isLeftPressed && !isRightPressed && !isUpPressed && !isDownPressed)
		SetActorRotation(FRotator(0, -90, 0));
	else if (!isSprint)
		doMovement = false;
}


void AFarmer::DisableMovement()
{
	UE_LOG(LogTemp, Warning, TEXT("Movement disabled"))
}


void AFarmer::EnableMovement()
{
	UE_LOG(LogTemp, Warning, TEXT("Movement enabled"))
}


void AFarmer::OnMoveUpPressed()
{
	isUpPressed = true;
}

void AFarmer::OnMoveDownPressed()
{
	isDownPressed = true;
}

void AFarmer::OnMoveLeftPressed()
{
	isLeftPressed = true;
}

void AFarmer::OnMoveRightPressed()
{
	isRightPressed = true;
}

void AFarmer::OnSprintPressed()
{
	GetCharacterMovement()->MaxWalkSpeed = 400;
	isSprint = true;
}

void AFarmer::OnMoveUpReleased()
{
	isUpPressed = false;
}

void AFarmer::OnMoveDownReleased()
{
	isDownPressed = false;
}

void AFarmer::OnMoveLeftReleased()
{
	isLeftPressed = false;
}

void AFarmer::OnMoveRightReleased()
{
	isRightPressed = false;
}

void AFarmer::OnSprintReleased()
{
	GetCharacterMovement()->MaxWalkSpeed = 200;
	isSprint = false;
}

void AFarmer::OnUseToolPressed()
{
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
	if (CurrentTool)
	{
		CurrentTool->Destroy();
	}

	Inventory->NextTool();
	CurrentTool = SpawnTool();
}

void AFarmer::OnInteractPressed()
{
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
			UE_LOG(LogTemp, Warning, TEXT("INTERACTION SUCCESS!"));
		}
	}
}

ATool* AFarmer::SpawnTool()
{
	TSubclassOf<ATool> ToolClass = Inventory->GetCurrentTool();
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	return GetWorld()->SpawnActor<ATool>(ToolClass, SpawnInfo);
}

void AFarmer::OnResetLevelPressed()
{
	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
}

void AFarmer::OnNextDayPressed()
{
	UGameplayStatics::OpenLevel(this, "Testing", false);
}