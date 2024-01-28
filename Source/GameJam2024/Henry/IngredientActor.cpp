// Fill out your copyright notice in the Description page of Project Settings.


#include "Henry/IngredientActor.h"

AIngredientActor::AIngredientActor() : AInteractableActor()
{
	SetInteractableType(INGREDIENT);
}

void AIngredientActor::Interaction()
{
}
