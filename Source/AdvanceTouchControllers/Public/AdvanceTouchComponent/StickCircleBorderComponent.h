// Copyright 2024 Tikhonov Gennadii, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "StickComponent.h"
#include "StickCircleBorderComponent.generated.h"


UCLASS(Blueprintable, ClassGroup=(TouchControl), meta=(BlueprintSpawnableComponent, DisplayName="StickCircleBorderComponent"))
class ADVANCETOUCHCONTROLLERS_API UStickCircleBorderComponent : public UStickComponent
{
	GENERATED_BODY()

public:
	UStickCircleBorderComponent();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, Category="Controller|Stick")
	float BorderRadius;
	
};
