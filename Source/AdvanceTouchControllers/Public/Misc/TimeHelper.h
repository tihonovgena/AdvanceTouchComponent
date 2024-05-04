// Copyright 2024 Tikhonov Gennadii, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "TimeHelper.generated.h"

UCLASS()
class ADVANCETOUCHCONTROLLERS_API UTimeHelper : public UObject
{
	GENERATED_BODY()

public:
	static double GetTotalSecondsBetweenDate(const FDateTime& StartDate, const FDateTime& EndDate);
	static double GetTotalSecondsOfDate(const FDateTime& DateTime);
};
