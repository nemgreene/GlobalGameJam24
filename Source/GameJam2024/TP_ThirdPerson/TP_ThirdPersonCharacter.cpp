// Copyright Epic Games, Inc. All Rights Reserved.

#include "TP_ThirdPersonCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// ATP_ThirdPersonCharacter

ATP_ThirdPersonCharacter::ATP_ThirdPersonCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = false; // Character moves in the direction of input...	
	//GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 50.0f), FRotator(0.0f, 0.0f, 50.0f));
	CameraBoom->TargetArmLength = 1600.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = false; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	PrimaryActorTick.bCanEverTick = true;


	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)

	// Capsule to pick up item
	TriggerCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("TriggerCapsule"));
	TriggerCapsule->SetupAttachment(RootComponent);
	TriggerCapsule->SetCollisionProfileName("Trigger");

}

void ATP_ThirdPersonCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	TriggerCapsule->OnComponentBeginOverlap.AddDynamic(this, &ATP_ThirdPersonCharacter::OnOverlapBegin);
	TriggerCapsule->OnComponentEndOverlap.AddDynamic(this, &ATP_ThirdPersonCharacter::OnCapsuleOverlapEnd);

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void ATP_ThirdPersonCharacter::SetCurrentStation(ABaseStationActor* Station)
{
	CurrentStation = Station;
}

ABaseStationActor* ATP_ThirdPersonCharacter::GetCurrentStation()
{
	return CurrentStation;
}

//////////////////////////////////////////////////////////////////////////
// Input

void ATP_ThirdPersonCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATP_ThirdPersonCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ATP_ThirdPersonCharacter::Look);

		// Pick up
		EnhancedInputComponent->BindAction(PickUpAction, ETriggerEvent::Started, this, &ATP_ThirdPersonCharacter::PickUp);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ATP_ThirdPersonCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// if right dir is + then mirror is false
		// else mirror is true

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ATP_ThirdPersonCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		//AddControllerYawInput(LookAxisVector.X);
		//AddControllerPitchInput(LookAxisVector.Y);
	}
}


// Check for item closest to the player and then attach it to the player
// Or drop the item at either station or on the floor
void ATP_ThirdPersonCharacter::PickUp(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Warning, TEXT("Pick up!"))

	// If already holding item, drop it
	if(HeldItem != nullptr)
	{
		// If dropped at station, check ingredient
		if(CurrentStation != nullptr && HeldItem->IsA<AIngredientActor>())
		{
			AIngredientActor* Ingredient = Cast<AIngredientActor>(HeldItem);
			bool Accepted = CurrentStation->CheckIngredient(Ingredient);

			HeldItem->SetPickedUp(false);

			// If not accepted, item stays on floor
			if(!Accepted)
			{
				TargetItem = HeldItem;
			}

			HeldItem = nullptr;
			return;
		}

		// Item on floor
		HeldItem->SetPickedUp(false);
		TargetItem = HeldItem;

		HeldItem = nullptr;
		return;
	}

	// Get targetted item if one selected
	if(TargetItem != nullptr)
	{
		//TargetItem->SetActorEnableCollision(false);
		TargetItem->SetPickedUp(true);

		HeldItem = TargetItem;
		TargetItem = nullptr;
	}
}

// Target item to pick up
void ATP_ThirdPersonCharacter::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//UE_LOG(LogTemp, Warning, TEXT("Something hit"))

	if(OtherActor && OtherActor->IsA<AInteractableActor>())
	{
		AInteractableActor* InteractableActor = Cast<AInteractableActor>(OtherActor);

		TargetItem = InteractableActor;
		//HeldItem->SetActorLocation(GetActorLocation());
		UE_LOG(LogTemp, Warning, TEXT("Interactable hit"))

	}
}

// Remove targetted item if leaving
void ATP_ThirdPersonCharacter::OnCapsuleOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//UE_LOG(LogTemp, Warning, TEXT("Something leaving"))

		if (OtherActor && OtherActor->IsA<AInteractableActor>())
		{
			AInteractableActor* InteractableActor = Cast<AInteractableActor>(OtherActor);

			if(TargetItem == InteractableActor)
			{
				TargetItem = nullptr;
			}

			//HeldItem->SetActorLocation(GetActorLocation());
			UE_LOG(LogTemp, Warning, TEXT("Interactable left"))

		}

}

// Called every frame
void ATP_ThirdPersonCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

      //UE_LOG(LogTemp, Warning, TEXT("hi"))
    if(HeldItem != nullptr)
    {
      FVector PlayerLocation = GetActorLocation();

      FVector InteractableLocation = HeldItem->GetActorLocation();

      FVector LerpedVector = FMath::Lerp(PlayerLocation + HeldItemOffset, InteractableLocation, DeltaTime);

      HeldItem->SetActorLocation(LerpedVector);
    }
	// if mirror is true then mirror the character
	// else don't mirror the character

	// look at point function FindLookAtRotation



	// Your code here
	// This code will be executed every frame
}
