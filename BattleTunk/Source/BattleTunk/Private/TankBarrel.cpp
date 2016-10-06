// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTunk.h"
#include "TankBarrel.h"




void UTankBarrel::Elevate(float RelativeSpeed)
{

	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1.0f, 1.0f);

	auto ElevationChange = RelativeSpeed * MaxDegreesPerSecond * this->GetWorld()->DeltaTimeSeconds;
	auto Elevation = FMath::Clamp<float>(RelativeRotation.Pitch + ElevationChange, MinElevation, MaxElevation);

	this->SetRelativeRotation(FRotator(Elevation, 0, 0));

}