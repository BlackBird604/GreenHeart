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
}

void AFarmer::Move()
{
	doMovement = true;
	/*if (isUpPressed && isRightPressed && !isLeftPressed && !isDownPressed)  //4 another direction movement
		SetActorRotation(FRotator(0, 45, 0));
	else if (isDownPressed && isRightPressed && !isLeftPressed && !isUpPressed)
		SetActorRotation(FRotator(0, 135, 0));
	else if (isDownPressed && isLeftPressed && !isRightPressed && !isUpPressed)
		SetActorRotation(FRotator(0, -135, 0));
	else if (isUpPressed && isLeftPressed && !isRightPressed && !isDownPressed)
		SetActorRotation(FRotator(0, -45, 0));
	else*/ if (isUpPressed && !isDownPressed && !isLeftPressed && !isRightPressed)
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