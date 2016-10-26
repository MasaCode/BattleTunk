// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TankAimingComponent.h" // To use EFiringState enum class.

#include "AIController.h"
#include "AITankController.generated.h" // Must be last include.


class UTankAimingComponent;

/**
 * 
 */
UCLASS()
class BATTLETUNK_API AAITankController : public AAIController
{
	GENERATED_BODY()

public:
	UFUNCTION()
		void OnTankDeath();

protected:
	virtual void SetPawn(APawn* InPawn) override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;


protected:
	UPROPERTY(EditDefaultsOnly, Category = Movement)
	float AcceptanceRadius = 8000.0f;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
		int32 RoundsLeft = 100;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
		float ReloadTimeInSecond = 2.0f;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
		float FireRange = 40000.0f;

private:
	APawn* mPlayerTank = nullptr;
	APawn* mTank = nullptr;
	UTankAimingComponent* mTankAimingComponent = nullptr;
	EFiringState FiringState = EFiringState::FS_Reloading;
	float mLastFiringTime = 0.0;
};
