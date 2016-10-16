// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTunk.h"
#include "AITankController.h"

#include "TankAimingComponent.h"
#include "Tank.h" // So we can impliment onDeath.

void AAITankController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn) {
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) return;

		PossessedTank->TankDeathDelegate.AddUniqueDynamic(this, &AAITankController::OnTankDeath);
	}
}

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
	
	if (!(mTankAimingComponent && mPlayerTank)) return;

	MoveToActor(mPlayerTank, AcceptanceRadius);
	mTankAimingComponent->AimAt(mPlayerTank->GetActorLocation());
	
	if (mTankAimingComponent->GetFiringState() == EFiringState::FS_Locked) {
		mTankAimingComponent->Fire();
	}

}

void AAITankController::OnTankDeath()
{
	APawn* Tank = this->GetPawn();
	if (!Tank) return;
	Tank->DetachFromControllerPendingDestroy();
}

