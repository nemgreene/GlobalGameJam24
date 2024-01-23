// Fill out your copyright notice in the Description page of Project Settings.


#include "Max/CPP_Actor_Max.h"

// Sets default values
ACPP_Actor_Max::ACPP_Actor_Max()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACPP_Actor_Max::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACPP_Actor_Max::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

