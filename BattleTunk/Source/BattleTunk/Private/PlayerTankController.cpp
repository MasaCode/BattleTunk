// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTunk.h"
#include "PlayerTankController.h"

#include "TankAimingComponent.h"
#include "Tank.h"

void APlayerTankController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	
	if (InPawn) {
		auto Tank = Cast<ATank>(InPawn);
		if (!ensure(Tank)) return;

		Tank->TankDeathDelegate.AddUniqueDynamic(this, &APlayerTankController::OnTankDeath);
	}


}

void APlayerTankController::BeginPlay()
{
	Super::BeginPlay();

	mTankAimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!mTankAimingComponent) {
		UE_LOG(LogTemp, Error, TEXT("AimingComponent not found"));
	}
	else {
		FoundAimingComponent(mTankAimingComponent);
	}
}

void APlayerTankController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (bGameEnd) return;

	AimTowardsCrosshair();
}

void APlayerTankController::OnTankDeath()
{
	PlayerDeath();
	
	//Enable mouse cursur.
	this->bShowMouseCursor = true;
	this->bEnableClickEvents = true;
	this->bEnableMouseOverEvents = true;

	//To not update camera.
	bGameEnd = true;

	this->StartSpectatingOnly();
}

void APlayerTankController::AimTowardsCrosshair()
{	
	if (!mTankAimingComponent) return;

	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation)) {
		// Hit the something and also got the Hit Location.
		mTankAimingComponent->AimAt(HitLocation);
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

	if (this->GetWorld()->LineTraceSingleByChannel(Hit, StartLocation, LineTraceEnd, ECollisionChannel::ECC_Camera)) {
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