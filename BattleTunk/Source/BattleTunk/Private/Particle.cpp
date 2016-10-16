// Copyright MasaCode

#include "BattleTunk.h"
#include "Particle.h"



UParticle::UParticle()
{
	this->bAutoActivate = false;
}

void UParticle::Explosion()
{
	this->Activate();
}