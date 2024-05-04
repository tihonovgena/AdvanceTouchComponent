// Copyright 2024 Tikhonov Gennadii, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "StickComponent.h"
#include "StickRectBorderComponent.generated.h"


UCLASS(Blueprintable, ClassGroup=(TouchControl), meta=(BlueprintSpawnableComponent, DisplayName="StickRectBorderComponent"))
class ADVANCETOUCHCONTROLLERS_API UStickRectBorderComponent : public UStickComponent
{
	GENERATED_BODY()

public:
	UStickRectBorderComponent();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, Category="Controller|Stick")
	FVector2D RectSize;
};
