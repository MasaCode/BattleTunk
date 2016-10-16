// Fill out your copyright notice in the Description page of Project Settings.

#pragma once



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



private:
	APawn* mPlayerTank = nullptr;
	UTankAimingComponent* mTankAimingComponent = nullptr;
};
