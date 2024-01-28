// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Henry/InteractableActor.h"
#include "IngredientActor.generated.h"

UENUM(BlueprintType)
enum IngredientType : uint8
{
	EGG UMETA(DisplayName = "Egg"),
	MILK UMETA(DisplayName = "Milk"),
	FLOUR UMETA(DisplayName = "Flour"),
	CANDLE UMETA(DisplayName = "Candle"),
	STREAMER UMETA(DisplayName = "Streamer"),
	FIREEXTINGUISHER UMETA(DisplayName = "Fire Extinguisher"),
};

/**
 * 
 */
UCLASS()
class GAMEJAM2024_API AIngredientActor : public AInteractableActor
{
	GENERATED_BODY()

public:
	AIngredientActor();

	virtual void Interaction() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ingredient")
		TEnumAsByte<IngredientType> IngredientName;


};
