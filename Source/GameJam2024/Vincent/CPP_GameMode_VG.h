// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CPP_GameMode_VG.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FSDayData
{
    GENERATED_BODY()

public:
    // Declare variables
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Index;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Title;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Level;
};




DECLARE_DYNAMIC_MULTICAST_DELEGATE(FInteracting);

UCLASS()
class GAMEJAM2024_API ACPP_GameMode_VG : public AGameModeBase
{
	GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FSDayData> DayList = { 
        {0, FString("Day 01"), FString("L_Day_1_MT")},
        {1, FString("Day 02"), FString("L_Day_2_MT")},
        {1, FString("Day 03"), FString("L_Day_3_MT")},
    };
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FSDayData ActiveDay;
};
