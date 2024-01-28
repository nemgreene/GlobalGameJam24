// Fill out your copyright notice in the Description page of Project Settings.


#include "Henry/FireStationActor.h"

AFireStationActor::AFireStationActor() : ABaseStationActor()
{
}

void AFireStationActor::Completion()
{
	Destroy();
}

void AFireStationActor::CheckFunction(AIngredientActor* Ingredient)
{
}

void AFireStationActor::BeginPlay()
{
	Super::BeginPlay();
}
