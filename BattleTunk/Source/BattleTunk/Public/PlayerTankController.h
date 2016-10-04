// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"

#include "GameFramework/PlayerController.h"
#include "PlayerTankController.generated.h" // Must be the last include.

/**
 * 
 */
UCLASS()
class BATTLETUNK_API APlayerTankController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	ATank* GetControlledTank() const;
	
	void AimTowardsCrosshair();

private:
	bool GetSightRayHitLocation(FVector& OUT_HitLocation) const;

private:
	ATank* mTank = nullptr;

};
