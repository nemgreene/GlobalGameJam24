// Fill out your copyright notice in the Description page of Project Settings.


#include "Henry/CPP_Actor_Henry.h"

// Sets default values
ACPP_Actor_Henry::ACPP_Actor_Henry()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACPP_Actor_Henry::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACPP_Actor_Henry::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

