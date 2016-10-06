// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTunk.h"
#include "TankTurret.h"


void UTankTurret::Azimuth(float RelativeSpeed) 
{
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1.0f, 1.0f);
	auto AzimuthChange = RelativeSpeed * MaxDegreesPerSecond * this->GetWorld()->DeltaTimeSeconds;
	auto Azimuth = FMath::Clamp<float>(RelativeRotation.Yaw + AzimuthChange, MinAzimuth, MaxAzimuth);

	this->SetRelativeRotation(FRotator(0, Azimuth, 0));
}

