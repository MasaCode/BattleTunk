// Fill out your copyright notice in the Description page of Project Settings.

#pragma once



#include "AIController.h"
#include "AITankController.generated.h" // Must be last include.

/**
 * 
 */

class ATank;
class UTankAimingComponent;

UCLASS()
class BATTLETUNK_API AAITankController : public AAIController
{
	GENERATED_BODY()

public:
		virtual void BeginPlay() override;
		virtual void Tick(float DeltaTime) override;

private:
	float AcceptanceRadius = 3000.0f;

	ATank* mPlayerTank = nullptr;
	UTankAimingComponent* mTankAimingComponent = nullptr;
};
