// Copyright 2024 Tikhonov Gennadii, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "DrawGeometryHelper.generated.h"

UCLASS()
class ADVANCETOUCHCONTROLLERS_API UDrawGeometryHelper : public UObject
{
	GENERATED_BODY()

public:
	static TArray<FVector2D> DrawRect(const FVector2D& Size, const FVector2D& Center);
	static TArray<FVector2D> DrawCircle(const float Radius, const int32 NumCircleSegments, const FVector2D& Center);
	
};
