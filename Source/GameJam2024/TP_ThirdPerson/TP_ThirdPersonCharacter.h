// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "InteractableActor.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "PaperZDCharacter.h"
#include "TP_ThirdPersonCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class ATP_ThirdPersonCharacter : public APaperZDCharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	/** Pick Up Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* PickUpAction;

public:
	ATP_ThirdPersonCharacter();
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool Mirror = false;

	virtual void Tick(float DeltaTime) override;

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	// Called for picking up items
	void PickUp(const FInputActionValue& Value);

	// Uses capsule collider to get an item from environment
	UFUNCTION()
		virtual void OnOverlapBegin
		(
			class UPrimitiveComponent* OverlappedComp,
			class AActor* OtherActor,
			class UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult);

	UFUNCTION()
		virtual void OnCapsuleOverlapEnd
		(
			UPrimitiveComponent* OverlappedComponent, 
			AActor* OtherActor, 
			UPrimitiveComponent* OtherComp, 
			int32 OtherBodyIndex);


protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay();

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	AInteractableActor* HeldItem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
		AInteractableActor* TargetItem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
		UCapsuleComponent* TriggerCapsule;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
		FVector HeldItemOffset = FVector(0,0,300.0f);
};

