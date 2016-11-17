// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 *  TnkTrack is used to set maxium driving force, and to apply forces to the tank.
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETUNK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
	
public:
	UTankTrack();

	virtual void BeginPlay() override;

	// Set Throttle between -1.0 and +1.0.
	UFUNCTION(BlueprintCallable, Category = Input)
	void SetThrottle(float Throttle);

	void SetItemEffects(float EffectsTime = 0.0f, float AdditionalDrivingForce = 0.0f);
	void DisableItemEffects();


private:
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
	
	void ApplyingSidewaysForce();
	void DriveTrack();

protected:
	// Max Force per track in Newtons.
	UPROPERTY(EditDefaultsOnly)
	float TrackMaxDrivingForce = 30000000.0f; 

private:
	float BaseTrackDrivingForce = 0.0f;
	float mCurrentThrottle = 0.0f;
	FTimerHandle TimerHandle;
	UStaticMeshComponent* mTankRoot = nullptr;
};
