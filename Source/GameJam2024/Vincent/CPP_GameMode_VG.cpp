// Fill out your copyright notice in the Description page of Project Settings.


#include "Vincent/CPP_GameMode_VG.h"

void ACPP_GameMode_VG::onInteract()
{
	OnInteracting.Broadcast();
}
