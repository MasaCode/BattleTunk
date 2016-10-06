// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTunk.h"
#include "TankTrack.h"


void UTankTrack::SetThrottle(float Throttle)
{
	auto Name = this->GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s : Throttle : %f"), *Name, Throttle);
	
	// TODO : clamp actual throttle value so that player can't over-drive.
	Throttle = FMath::Clamp<float>(Throttle, -1.0f, 1.0f);
	auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	
	auto TankRoot = Cast<UPrimitiveComponent>(this->GetOwner()->GetRootComponent()); // UP TO the Tank itself and go to root component (body UStaticMeshComponent casts as a UPrimitiveComponent (this is the base class of UStaticMeshComponent.))
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}

