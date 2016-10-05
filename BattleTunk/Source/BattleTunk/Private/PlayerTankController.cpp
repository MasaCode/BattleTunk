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
		// Hit the something and also got the Hit Location.
		mTank->AimAt(HitLocation);
	}

}

bool APlayerTankController::GetSightRayHitLocation(FVector& OUT_HitLocation) const
{	
	// Gettting the size of viewPort.
	int32 viewportSizeX, viewPortSizeY;
	this->GetViewportSize(viewportSizeX, viewPortSizeY);

	// Getting the location of where the tank aiming to.
	FVector2D ScreenLocation;
	ScreenLocation.X = CrossHairLocationX * viewportSizeX;
	ScreenLocation.Y = CrossHairLocationY * viewPortSizeY;

	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection)) {
		// Line Tracing.
		 return GetLookVectorHitLocation(LookDirection, OUT_HitLocation);
	}

	return false;
}

bool APlayerTankController::GetLookVectorHitLocation(const FVector& LookDirection, FVector& OUT_HitLocation) const
{
	FVector StartLocation = this->PlayerCameraManager->GetCameraLocation();
	FVector LineTraceEnd = StartLocation + LineTraceRange * LookDirection;
	FHitResult Hit;

	if (this->GetWorld()->LineTraceSingleByChannel(Hit, StartLocation, LineTraceEnd, ECollisionChannel::ECC_Visibility)) {
		OUT_HitLocation = Hit.Location;
		return true;
	}

	OUT_HitLocation = FVector(0.0f);
	return false;
}

//@brief
// Getting the Look Direction.
bool APlayerTankController::GetLookDirection(const FVector2D& ScreenLocation, FVector& OUT_LookDirection) const
{
	FVector CameraWorldLocation;	
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, OUT_LookDirection);
}