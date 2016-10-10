// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTunk.h"
#include "AITankController.h"

#include "Tank.h"
#include "TankAimingComponent.h"

void AAITankController::BeginPlay()
{
	Super::BeginPlay();


	mTankAimingComponent = Cast<ATank>(GetPawn())->FindComponentByClass<UTankAimingComponent>();
	mPlayerTank = Cast<ATank>(this->GetWorld()->GetFirstPlayerController()->GetPawn());
	
	if (!(mTankAimingComponent && mPlayerTank)) {
		UE_LOG(LogTemp, Error, TEXT("Component not found."));
	}
	
}

void AAITankController::Tick(float DeltaTime) 
{
	Super::Tick(DeltaTime);
	
	if (!ensure(mTankAimingComponent && mPlayerTank)) return;

	MoveToActor(mPlayerTank, AcceptanceRadius);

	{ // Firing!!!!
		mTankAimingComponent->AimAt(mPlayerTank->GetActorLocation());
		mTankAimingComponent->Fire();
	}
}
