// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTunk.h"
#include "AITankController.h"

#include "TankAimingComponent.h"

void AAITankController::BeginPlay()
{
	Super::BeginPlay();


	mTankAimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	mPlayerTank = this->GetWorld()->GetFirstPlayerController()->GetPawn();
	
	if (!(mTankAimingComponent && mPlayerTank)) {
		UE_LOG(LogTemp, Error, TEXT("Component not found."));
	}
	
}

void AAITankController::Tick(float DeltaTime) 
{
	Super::Tick(DeltaTime);
	
	if (!ensure(mTankAimingComponent && mPlayerTank)) return;

	MoveToActor(mPlayerTank, AcceptanceRadius);
	mTankAimingComponent->AimAt(mPlayerTank->GetActorLocation());
	
	if (mTankAimingComponent->GetFiringState() == EFiringState::FS_Locked) {
		mTankAimingComponent->Fire();
	}

}
