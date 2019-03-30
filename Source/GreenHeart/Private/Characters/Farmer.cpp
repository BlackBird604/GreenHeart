// The Green Heart @Politechnika Opolska

#include "Farmer.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"

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

	bUseControllerRotationYaw = false;
}

void AFarmer::BeginPlay()
{
	Super::BeginPlay();
	
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