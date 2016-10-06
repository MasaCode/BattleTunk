// Fill out your copyright notice in the Description page of Project Settings.

#pragma once



#include "GameFramework/PlayerController.h"
#include "PlayerTankController.generated.h" // Must be the last include.

/**
 * 
 */

class ATank;

UCLASS()
class BATTLETUNK_API APlayerTankController : public APlayerController
{
	GENERATED_BODY()
	
public: // For public member functions.
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	ATank* GetControlledTank() const;
	
	void AimTowardsCrosshair();

private: // For private member functions.
	bool GetSightRayHitLocation(FVector& OUT_HitLocation) const;
	bool GetLookDirection(const FVector2D& ScreenLocation, FVector& OUT_LookDirection) const;
	bool GetLookVectorHitLocation(const FVector& LookDirection, FVector& OUT_HitLocation) const;

public: // For public member variables.

	UPROPERTY(EditDefaultsOnly)
		float CrossHairLocationX = 0.5f;
	UPROPERTY(EditDefaultsOnly)
		float CrossHairLocationY = 0.3333;
	UPROPERTY(EditDefaultsOnly)
		float LineTraceRange = 1000000.0f; // 10km.

private: // For private member variables.
	ATank* mTank = nullptr;
	

};
