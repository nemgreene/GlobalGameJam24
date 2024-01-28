// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "InteractableActor.generated.h"

UENUM(BlueprintType)
enum InteractableType : uint8
{
	INGREDIENT UMETA(DisplayName = "Ingredient"),
	TOOL UMETA(DisplayName = "Tool"),
};

UCLASS()
class GAMEJAM2024_API AInteractableActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractableActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// This runs (or can run?) if the object is picked up
	// Intention is to override this for unique objects
	virtual void Interaction();

	// Getters and setters for IsPickedUp variable
	bool GetPickedUp();

	void SetPickedUp(bool b);

	InteractableType GetInteractableType();

	void SetInteractableType(InteractableType t);

	void SetBoxComponentPhysics(bool b);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
		UBoxComponent* BoxComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
		USceneComponent* DefaultSceneRoot;

private:
	bool IsPickedUp;

	TEnumAsByte <InteractableType> Type;
};
