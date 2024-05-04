// Copyright 2024 Tikhonov Gennadii, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Enums/ControllerAlignment.h"

#include "ViewportHelper.generated.h"

UCLASS()
class ADVANCETOUCHCONTROLLERS_API UViewportHelper : public UObject
{
	GENERATED_BODY()

public:
	static FVector2D GetAlignmentPosition(const UWorld* World, const EControllerAlignment::Type Alignment);
	static FVector2D GetRectAlignmentPosition(const UWorld* World, const FVector2D& Size, const EControllerAlignment::Type Alignment);
	static FVector2D GetCircleAlignmentPosition(const UWorld* World, const float Radius, const EControllerAlignment::Type Alignment);
	static FVector2D GetAlignmentValue(const EControllerAlignment::Type Alignment);

	static void AdjustPositionWithOffset(FVector2D& AdjustPosition, const FVector2D Offset, const EControllerAlignment::Type Alignment);
	
	static FViewport* GetViewport(const UWorld* World);
	static UGameViewportClient* GetGameViewportClient(const UWorld* World);
	static FVector2D GetViewportSize(const UWorld* World);
	
	static float GetDPIScale(const UWorld* World);
};
