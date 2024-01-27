// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "InteractableActor.generated.h"

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
	enum InteractableType
	{
		INGREDIENT,
		TOOL,
	};

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// This runs (or can run?) if the object is picked up
	// Intention is to override this for unique objects
	virtual void Interaction();

	// Getters and setters for IsPickedUp variable
	bool GetPickedUp();

	void SetPickedUp(bool b);

	void SetBoxComponentPhysics(bool b);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
		UBoxComponent* BoxComponent;

private:
	bool IsPickedUp;
};
