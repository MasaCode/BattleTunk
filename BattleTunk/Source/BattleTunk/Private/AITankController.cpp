// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTunk.h"
#include "AITankController.h"

#include "Tank.h" // So we can impliment onDeath.

void AAITankController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn) {
		mTank = InPawn;
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
	
	mLastFiringTime = this->GetWorld()->GetTimeSeconds();
}

void AAITankController::Tick(float DeltaTime) 
{
	Super::Tick(DeltaTime);
	if (!(mTankAimingComponent && mPlayerTank)) return;

	MoveToActor(mPlayerTank, AcceptanceRadius);
	
	FVector AILocation = mTank->GetActorLocation();
	FVector PlayerLocation = mPlayerTank->GetActorLocation();
	FVector Distance = PlayerLocation - AILocation;

	if (FMath::Sqrt(Distance.X*Distance.X + Distance.Y*Distance.Y) > FireRange) return;
	
	mTankAimingComponent->AimAt(PlayerLocation);

	auto currentTime = this->GetWorld()->GetTimeSeconds();
	if (RoundsLeft <= 0) {
		FiringState = EFiringState::FS_OutOfAmo;
	}
	else if (((currentTime - mLastFiringTime) < ReloadTimeInSecond)) {
		FiringState = EFiringState::FS_Reloading;
	}
	else if (mTankAimingComponent->IsBarrelMoving()) {
		FiringState = EFiringState::FS_Aiming;
	}
	else {
		FiringState = EFiringState::FS_Locked;
	}

	if(FiringState == EFiringState::FS_Locked){
		mTankAimingComponent->Fire();
		mLastFiringTime = this->GetWorld()->GetTimeSeconds();
		RoundsLeft--;
	}


}

void AAITankController::OnTankDeath()
{
	APawn* Tank = this->GetPawn();
	if (!Tank) return;
	Tank->DetachFromControllerPendingDestroy();
}

