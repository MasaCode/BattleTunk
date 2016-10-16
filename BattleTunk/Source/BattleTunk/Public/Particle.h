// Copyright MasaCode

#pragma once

#include "Particles/ParticleSystemComponent.h"
#include "Particle.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETUNK_API UParticle : public UParticleSystemComponent
{
	GENERATED_BODY()
	
public:
	UParticle();
	void Explosion();
	
};
