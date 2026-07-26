// Copyright Epic Games, Inc. All Rights Reserved.

#include "GAM415_MainProjectPickUpComponent.h"

UGAM415_MainProjectPickUpComponent::UGAM415_MainProjectPickUpComponent()
{
	// Setup the Sphere Collision
	SphereRadius = 32.f;
}

void UGAM415_MainProjectPickUpComponent::BeginPlay()
{
	Super::BeginPlay();

	// Register our Overlap Event
	OnComponentBeginOverlap.AddDynamic(this, &UGAM415_MainProjectPickUpComponent::OnSphereBeginOverlap);
}

void UGAM415_MainProjectPickUpComponent::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Checking if it is a First Person Character overlapping
	AGAM415_MainProjectCharacter* Character = Cast<AGAM415_MainProjectCharacter>(OtherActor);
	if(Character != nullptr)
	{
		// Notify that the actor is being picked up
		OnPickUp.Broadcast(Character);

		// Unregister from the Overlap Event so it is no longer triggered
		OnComponentBeginOverlap.RemoveAll(this);
	}
}
