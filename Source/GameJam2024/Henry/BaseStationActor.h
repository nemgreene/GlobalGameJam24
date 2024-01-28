// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IngredientActor.h"
#include "BaseStationActor.generated.h"

class UCapsuleComponent;

UCLASS()
class GAMEJAM2024_API ABaseStationActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseStationActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Completion();

	bool CheckIngredient(AIngredientActor* Ingredient);

	virtual void CheckFunction(AIngredientActor* Ingredient);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
		TArray<TEnumAsByte<IngredientType>> IngredientsList;

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collection")
		UCapsuleComponent* TriggerCapsule;

};
