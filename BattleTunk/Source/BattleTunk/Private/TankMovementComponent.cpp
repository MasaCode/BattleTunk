// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTunk.h"
#include "TankMovementComponent.h"

#include "TankTrack.h"



void UTankMovementComponent::Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float  Throw)
{
	if (!LeftTrack || !RightTrack) return;

	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}


void UTankMovementComponent::IntendTurnRight(float Throw) 
{
	if (!LeftTrack || !RightTrack) return;

	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) 
{
	// No need to call super as we're replacing the functionality of this method.
	FVector AIForwardIntention = MoveVelocity.GetSafeNormal();
	FVector TankForward = GetOwner()->GetActorForwardVector();

	IntendTurnRight(FVector::CrossProduct(TankForward, AIForwardIntention).Z);
	IntendMoveForward(FVector::DotProduct(TankForward, AIForwardIntention));

}