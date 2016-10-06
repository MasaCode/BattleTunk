// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 *  TnkTrack is used to set maxium driving force, and to apply forces to the tank.
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETUNK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
	
public:
	// Set Throttle between -1.0 and +1.0.
	UFUNCTION(BlueprintCallable, Category = Input)
	void SetThrottle(float Throttle);
	
};
