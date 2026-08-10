// Copyright Epic Games, Inc. All Rights Reserved.

#include "GAM415_MainProjectProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/SphereComponent.h"
#include "Components/DecalComponent.h"
#include "Kismet/GameplayStatics.h"	
#include "NiagaraFunctionLibrary.h"		// **Reference spawn function for Niagara particle system
#include "NiagaraComponent.h"			// **Implementation of Niagara component
#include "PerlinProcTerrain.h"			// ***Reference to the PerlinProcTerrain class for the Niagara particle system





AGAM415_MainProjectProjectile::AGAM415_MainProjectProjectile() 
{
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &AGAM415_MainProjectProjectile::OnHit);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// *Create a static mesh component for the ball
	ballMesh = CreateDefaultSubobject<UStaticMeshComponent>("Ball Mesh");

	// Set as root component
	RootComponent = CollisionComp;

	// *Attach the mesh to the collision component
	ballMesh->SetupAttachment(CollisionComp);

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;
}

// *Called when the game starts or when spawned, here we will set the random color for the ball and create a dynamic material instance for it
void AGAM415_MainProjectProjectile::BeginPlay()
{
	Super::BeginPlay();
	randColor = FLinearColor(UKismetMathLibrary::RandomFloatInRange(0.f, 1.f), UKismetMathLibrary::RandomFloatInRange(0.f, 1.f), UKismetMathLibrary::RandomFloatInRange(0.f, 1.f), 1.f);

	dmiMat = UMaterialInstanceDynamic::Create(projMat, this);
	ballMesh->SetMaterial(0, dmiMat);

	dmiMat->SetVectorParameterValue("ProjColor", randColor);
	
}


void AGAM415_MainProjectProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());

		Destroy();
	}

	// **Check if the OtherActor is valid before proceeding with spawning the Niagara particle system and decal
	if (OtherActor != nullptr)
	{
		
		// **Check if the Niagara particle system is valid before spawning it
		if (colorP)
		{

			// **Spawn a Niagara particle system at the hit location with a random color
			UNiagaraComponent* particleComp = UNiagaraFunctionLibrary::SpawnSystemAttached(colorP, HitComp, NAME_None, FVector(-20.f, 0.f, 0.f), FRotator(0.f), EAttachLocation::KeepRelativeOffset, true);

			// **Set the random color for the Niagara particle system
			particleComp->SetNiagaraVariableLinearColor(FString("RandomColorP"), randColor);
			// **Destroy the ball mesh and disable collision after spawning the particle system
			ballMesh->DestroyComponent();
			CollisionComp->BodyInstance.SetCollisionProfileName("NoCollision");
		}
		
		float frameNum = UKismetMathLibrary::RandomFloatInRange(0.f, 3.f);

		auto Decal = UGameplayStatics::SpawnDecalAtLocation(GetWorld(), baseMat, FVector(UKismetMathLibrary::RandomFloatInRange(20.f, 40.f)), Hit.Location, Hit.Normal.Rotation(), 0.f);
		auto MatInstance = Decal->CreateDynamicMaterialInstance();

		MatInstance->SetVectorParameterValue("Color", randColor);
		MatInstance->SetScalarParameterValue("Frame", frameNum);

		// *** Check if the OtherActor is of type APerlinProcTerrain, if it is, call the AlterMesh function to modify the procedural mesh based on the impact point of the projectile
		APerlinProcTerrain* procTerrain = Cast<APerlinProcTerrain>(OtherActor);

		if(procTerrain)
		{
			procTerrain->AlterMesh(Hit.ImpactPoint);
		}
	}
}