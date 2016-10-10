// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTunk.h"
#include "AITankController.h"

#include "Tank.h"

void AAITankController::BeginPlay()
{
	Super::BeginPlay();
	
	mTank = Cast<ATank>(GetPawn());
	mPlayerTank = Cast<ATank>(this->GetWorld()->GetFirstPlayerController()->GetPawn());
	
	if (!(mTank && mPlayerTank)) {
		UE_LOG(LogTemp, Error, TEXT("Component not found."));
	}
	
}

void AAITankController::Tick(float DeltaTime) 
{
	Super::Tick(DeltaTime);
	
	if (!ensure(mTank && mPlayerTank)) return;

	MoveToActor(mPlayerTank, AcceptanceRadius);


	{ // Firing!!!!
		mTank->AimAt(mPlayerTank->GetActorLocation());
		mTank->Fire();
	}
}
