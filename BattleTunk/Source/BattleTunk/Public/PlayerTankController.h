// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TankAimingComponent.h" // To use EFiringState enum class.

#include "GameFramework/PlayerController.h"
#include "PlayerTankController.generated.h" // Must be the last include.

class UTankAimingComponent;
/**
 * Responsible for helping the player aim.
 */
UCLASS()
class BATTLETUNK_API APlayerTankController : public APlayerController
{
	GENERATED_BODY()
	
public: // For public member functions.
	UFUNCTION()
	void OnTankDeath();

	void AimTowardsCrosshair();

	// Because I want to call this function from outside of this class.
	UFUNCTION(BlueprintCallable, Category = State)
		void GetLastFireTime();

	UFUNCTION(BlueprintCallable, Category = State)
		bool CanFire();

	UFUNCTION(BlueprintCallable, Category = State)
		int32 GetRoundsLeft();

	UFUNCTION(BlueprintCallable, Category = State)
		bool IsPlayerAlive();

protected:
	virtual void SetPawn(APawn* InPawn) override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent, Category = Setup)
		void FoundAimingComponent(UTankAimingComponent* AimingCompRef);

	UFUNCTION(BlueprintImplementableEvent, Category = Death)
		void PlayerDeath();

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

	UPROPERTY(BlueprintReadOnly, Category = State)
		EFiringState FiringState = EFiringState::FS_Reloading;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
		int32 RoundsLeft = 100;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
		float ReloadTimeInSecond = 2.0f;

protected: // For private member variables.
	UPROPERTY(BlueprintReadOnly, Category = State)
		UTankAimingComponent* mTankAimingComponent = nullptr;
	
private:
	bool bGameEnd = false;
	float mLastFiringTime = 0.0;

};
