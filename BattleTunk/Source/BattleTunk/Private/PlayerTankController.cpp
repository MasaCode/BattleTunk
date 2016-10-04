// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTunk.h"
#include "PlayerTankController.h"



void APlayerTankController::BeginPlay() 
{
	Super::BeginPlay();

	 mTank = GetControlledTank();
	if (!mTank) {
		UE_LOG(LogTemp, Error, TEXT("Controlled Tank not found"));
	}
	
}

void APlayerTankController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();

}


ATank* APlayerTankController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void APlayerTankController::AimTowardsCrosshair()
{	
	if (!mTank) return;

	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation)) {
		UE_LOG(LogTemp, Warning, TEXT("Hit Location : %s"), *HitLocation.ToString());
	}

}

bool APlayerTankController::GetSightRayHitLocation(FVector& OUT_HitLocation) const
{


	return false;
}