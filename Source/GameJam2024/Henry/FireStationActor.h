// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Henry/BaseStationActor.h"
#include "FireStationActor.generated.h"

/**
 * 
 */
UCLASS()
class GAMEJAM2024_API AFireStationActor : public ABaseStationActor
{
	GENERATED_BODY()

public:

	AFireStationActor();

	virtual void Completion() override;

	virtual void CheckFunction(AIngredientActor* Ingredient) override;

protected:
	virtual void BeginPlay() override;
};
