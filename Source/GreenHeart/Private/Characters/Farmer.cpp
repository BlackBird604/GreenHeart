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

#include "Actors/Tools/Tool.h"
#include "Components/InventoryComponent.h"

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
	if (MovementInputs > 0)
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

	InputComponent->BindAction("MoveUp", IE_Released, this, &AFarmer::OnMoveUpReleased);
	InputComponent->BindAction("MoveDown", IE_Released, this, &AFarmer::OnMoveDownReleased);
	InputComponent->BindAction("MoveLeft", IE_Released, this, &AFarmer::OnMoveLeftReleased);
	InputComponent->BindAction("MoveRight", IE_Released, this, &AFarmer::OnMoveRightReleased);

	InputComponent->BindAction("UseTool", IE_Pressed, this, &AFarmer::OnUseToolPressed);
	InputComponent->BindAction("UseTool", IE_Released, this, &AFarmer::OnUseToolReleased);
	InputComponent->BindAction("NextTool", IE_Pressed, this, &AFarmer::OnNextToolPressed);
}

void AFarmer::OnMoveUpPressed()
{
	SetActorRotation(FRotator(0, 0, 0));
	MovementInputs++;
}

void AFarmer::OnMoveDownPressed()
{
	SetActorRotation(FRotator(0, 180, 0));
	MovementInputs++;
}

void AFarmer::OnMoveLeftPressed()
{
	SetActorRotation(FRotator(0, -90, 0));
	MovementInputs++;
}

void AFarmer::OnMoveRightPressed()
{
	SetActorRotation(FRotator(0, 90, 0));
	MovementInputs++;
}

void AFarmer::OnMoveUpReleased()
{
	DecrementMovementInputs();
}

void AFarmer::OnMoveDownReleased()
{
	DecrementMovementInputs();
}

void AFarmer::OnMoveLeftReleased()
{
	DecrementMovementInputs();
}

void AFarmer::OnMoveRightReleased()
{
	DecrementMovementInputs();
}

void AFarmer::DecrementMovementInputs()
{
	MovementInputs--;
	if (MovementInputs < 0)
	{
		MovementInputs = 0;
	}
}

void AFarmer::OnUseToolPressed()
{
	GetWorld()->GetTimerManager().SetTimer(ToolChargeTimer, this, &AFarmer::ChargeTool, 1.0f, true, 0.0f);
}

void AFarmer::ChargeTool()
{
	if (CurrentTool)
	{
		CurrentTool->Charge();
	}
}

void AFarmer::OnUseToolReleased()
{
	GetWorld()->GetTimerManager().ClearTimer(ToolChargeTimer);
	if (CurrentTool)
	{
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

ATool* AFarmer::SpawnTool()
{
	TSubclassOf<ATool> ToolClass = Inventory->GetCurrentTool();
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	return GetWorld()->SpawnActor<ATool>(ToolClass, SpawnInfo);
}