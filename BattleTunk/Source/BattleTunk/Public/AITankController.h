// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"

#include "AIController.h"
#include "AITankController.generated.h" // Must be last include.

/**
 * 
 */
UCLASS()
class BATTLETUNK_API AAITankController : public AAIController
{
	GENERATED_BODY()

public:
		virtual void BeginPlay() override;
		virtual void Tick(float DeltaTime) override;
	

		ATank* GetControlledTank() const;
		void FindPlayerControlledTank();


private:
	ATank* mPlayerTank = nullptr;
	ATank* mTank = nullptr;
};
