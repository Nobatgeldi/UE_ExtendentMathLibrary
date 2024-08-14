// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CV_Intern_Functions.generated.h"

/**
 * 
 */
UCLASS()
class CV_INTERN_API UCV_Intern_Functions : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Centroid", Keywords = "Covisart"), Category = "Covisart|Functions")
	static FVector CalculateCentroid(UPARAM(ref)TArray<FVector>&Points);
};
