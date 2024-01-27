// Fill out your copyright notice in the Description page of Project Settings.


#include "Henry/InteractableActor.h"

// Sets default values
AInteractableActor::AInteractableActor() : IsPickedUp(false)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->SetSimulatePhysics(true);
	BoxComponent->SetEnableGravity(true);

	RootComponent = BoxComponent;
	//BoxComponent->SetCollisionProfileName("");
}

// Called when the game starts or when spawned
void AInteractableActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInteractableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInteractableActor::Interaction()
{
}

bool AInteractableActor::GetPickedUp()
{
	return IsPickedUp;
}

void AInteractableActor::SetPickedUp(bool b)
{
	IsPickedUp = b;
	SetBoxComponentPhysics(!b);
}

void AInteractableActor::SetBoxComponentPhysics(bool b)
{
	BoxComponent->SetSimulatePhysics(b);
	BoxComponent->SetEnableGravity(b);
}

