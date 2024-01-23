// Fill out your copyright notice in the Description page of Project Settings.


#include "Clayton/CPP_Actor_Clayton.h"

// Sets default values
ACPP_Actor_Clayton::ACPP_Actor_Clayton()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACPP_Actor_Clayton::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACPP_Actor_Clayton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

