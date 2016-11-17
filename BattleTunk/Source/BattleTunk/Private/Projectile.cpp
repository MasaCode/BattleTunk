// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTunk.h"
#include "Projectile.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Adding the projectile component to this projectile.
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movement"));
	ProjectileMovement->bAutoActivate = false;
	//ProjectileMovement->PrimaryComponentTick.bCanEverTick = false;

	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision Mesh"));
	SetRootComponent(CollisionMesh);
	CollisionMesh->SetNotifyRigidBodyCollision(true); // set sumulation Generates hit events.
	CollisionMesh->SetVisibility(false);
	CollisionMesh->PrimaryComponentTick.bCanEverTick = false;

	LaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Launch Blast"));
	LaunchBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	LaunchBlast->bAutoActivate = true;
	
	ImpactBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Impact Blast"));
	ImpactBlast->bAutoActivate = false;
	ImpactBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	
	ExplosionForce = CreateDefaultSubobject<URadialForceComponent>(FName("Exploision Force"));
	ExplosionForce->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	ExplosionForce->ImpulseStrength = 50000000.0f;
	ExplosionForce->Radius = 500.0f;
	ExplosionForce->PrimaryComponentTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	CollisionMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}


void AProjectile::LaunchProjectile(float LaunchSpeed) 
{
	ProjectileMovement->SetVelocityInLocalSpace(FVector::ForwardVector * LaunchSpeed);
	ProjectileMovement->Activate();

	
	UGameplayStatics::PlaySoundAtLocation(this->GetWorld(), LaunchSound, this->GetActorLocation());
}

void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	LaunchBlast->Deactivate();
	ImpactBlast->Activate();

	ExplosionForce->FireImpulse();	
	SetRootComponent(ImpactBlast);
	CollisionMesh->DestroyComponent();

	UGameplayStatics::ApplyRadialDamage(this, ProjectileDamage, this->GetActorLocation(), ExplosionForce->Radius, UDamageType::StaticClass(), TArray<AActor*>());
	
	
	UGameplayStatics::PlaySoundAtLocation(this->GetWorld(), ExplosionSound, this->GetActorLocation());


	FTimerHandle Handle;
	this->GetWorld()->GetTimerManager().SetTimer(Handle, this, &AProjectile::DestroyProjectile, DestroyDelay,false);
}

void AProjectile::DestroyProjectile()
{
	Destroy();
}