// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTunk.h"
#include "TankTurret.h"


UTankTurret::UTankTurret()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTurret::Rotate(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1.0f, 1.0f);
	auto RotationChange = RelativeSpeed * MaxDegreesPerSecond * this->GetWorld()->DeltaTimeSeconds;
	auto Rotation = RotationChange + RelativeRotation.Yaw;

	this->SetRelativeRotation(FRotator(0, Rotation, 0));
}

