// Fill out your copyright notice in the Description page of Project Settings.


#include "Henry/BaseStationActor.h"
#include "Components/CapsuleComponent.h"
#include "TP_ThirdPerson/TP_ThirdPersonCharacter.h"

// Sets default values
ABaseStationActor::ABaseStationActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TriggerCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("TriggerCapsule"));
	TriggerCapsule->SetupAttachment(RootComponent);
	TriggerCapsule->SetCollisionProfileName("Trigger");

}

// Called when the game starts or when spawned
void ABaseStationActor::BeginPlay()
{
	Super::BeginPlay();

	TriggerCapsule->OnComponentBeginOverlap.AddDynamic(this, &ABaseStationActor::OnOverlapBegin);
	TriggerCapsule->OnComponentEndOverlap.AddDynamic(this, &ABaseStationActor::OnCapsuleOverlapEnd);
}

// Called every frame
void ABaseStationActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseStationActor::Completion()
{
	
}

// Check dropped item to see if its in the list
bool ABaseStationActor::CheckIngredient(AIngredientActor* Ingredient)
{
	TEnumAsByte<IngredientType> IngredientName = Ingredient->IngredientName;

	if(IngredientsList.Contains(IngredientName))
	{
		IngredientsList.RemoveSingle(IngredientName);
				
		//Ingredient->Destroy();		

		CheckFunction(Ingredient);

		if(IngredientsList.IsEmpty())
		{
			OnBlocking.Broadcast();
			Completion();
		}
		return true;
	}
	return false;
}

void ABaseStationActor::CheckFunction(AIngredientActor* Ingredient)
{
	Ingredient->Destroy();
}

void ABaseStationActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Check player entered trigger component
	if (OtherActor && OtherActor->IsA<ATP_ThirdPersonCharacter>())
	{
		// If player enters trigger
		ATP_ThirdPersonCharacter* Player = Cast<ATP_ThirdPersonCharacter>(OtherActor);

		// Set the players current station for if the player drops the item
		if(Player->GetCurrentStation() == nullptr)
		{
			Player->SetCurrentStation(this);
		}
	}
}

void ABaseStationActor::OnCapsuleOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	// Check player entered trigger component
	if (OtherActor && OtherActor->IsA<ATP_ThirdPersonCharacter>())
	{
		// If player enters trigger
		ATP_ThirdPersonCharacter* Player = Cast<ATP_ThirdPersonCharacter>(OtherActor);

		// Remove station
		Player->SetCurrentStation(nullptr);
	}
}

