// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTunk.h"
#include "TankTrack.h"


UTankTrack::UTankTrack() 
{
	PrimaryComponentTick.bCanEverTick = false;
	bWantsBeginPlay = true;
}

void UTankTrack::BeginPlay() 
{
	Super::BeginPlay();

	mTankRoot = Cast<UStaticMeshComponent>(this->GetOwner()->GetRootComponent());
	if (!mTankRoot) {
		UE_LOG(LogTemp, Error, TEXT("Tank Root Component not found."));
	}
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);

	BaseTrackDrivingForce = TrackMaxDrivingForce;
}


void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	DriveTrack();
	ApplyingSidewaysForce();
	mCurrentThrottle = 0.0f;
}

void UTankTrack::ApplyingSidewaysForce()
{
	if (!mTankRoot) return;


	float SlippageSpeed = FVector::DotProduct(this->GetRightVector(), this->GetComponentVelocity());
	// work-out the required acceleration this frame to correct
	float DeltaTime = this->GetWorld()->GetDeltaSeconds();
	auto CorrectionnAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();
	// Calculate and apply sideway for (F = m * a).
	auto CorrectionForce = (mTankRoot->GetMass() * CorrectionnAcceleration) / 2;
	mTankRoot->AddForce(CorrectionForce);
}

void UTankTrack::SetThrottle(float Throttle)
{
	//mCurrentThrottle = FMath::Clamp<float>(mCurrentThrottle + Throttle, -1.0f, 1.0f);
	mCurrentThrottle += Throttle;
}

void UTankTrack::DriveTrack()
{
	auto ForceApplied = GetForwardVector() * mCurrentThrottle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(this->GetOwner()->GetRootComponent()); // UP TO the Tank itself and go to root component (body UStaticMeshComponent casts as a UPrimitiveComponent (this is the base class of UStaticMeshComponent.))
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}

void UTankTrack::SetItemEffects(float EffectsTime, float AdditionalDrivingForce)
{
	TrackMaxDrivingForce += AdditionalDrivingForce;
	this->GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
	this->GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UTankTrack::DisableItemEffects, EffectsTime, false);

}

void UTankTrack::DisableItemEffects()
{
	TrackMaxDrivingForce = BaseTrackDrivingForce;
	this->GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
}

