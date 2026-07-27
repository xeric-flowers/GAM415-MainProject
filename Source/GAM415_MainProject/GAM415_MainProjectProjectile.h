// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GAM415_MainProjectProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UNiagaraSystem; // **Forward declaration of UNiagaraSystem class

UCLASS(config=Game)
class AGAM415_MainProjectProjectile : public AActor
{
	GENERATED_BODY()

	/** Sphere collision component */
	UPROPERTY(VisibleDefaultsOnly, Category=Projectile)
	USphereComponent* CollisionComp;

	/** Projectile movement component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* ProjectileMovement;

	// *Static mesh component for the ball

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* ballMesh;
	
	UPROPERTY(EditAnywhere)
		UMaterial* baseMat;

	// *Dynamic material instance for the ball
	UPROPERTY()
	FLinearColor randColor;

	UPROPERTY(EditAnywhere)
	UMaterialInterface* projMat;

	UPROPERTY()
	UMaterialInstanceDynamic* dmiMat;

	// **Setting up Niagara system for particle effect when the projectile hits something
	UPROPERTY(EditAnywhere)
	UNiagaraSystem* colorP;


public:
	AGAM415_MainProjectProjectile();

	// *Add beginplay function when the projectile is spawned
protected:
	virtual void BeginPlay();

	/** called when projectile hits something */
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	/** Returns CollisionComp subobject **/
	USphereComponent* GetCollisionComp() const { return CollisionComp; }
	/** Returns ProjectileMovement subobject **/
	UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }
};

