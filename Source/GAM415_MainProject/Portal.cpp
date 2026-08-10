// Fill out your copyright notice in the Description page of Project Settings.


#include "Portal.h"
#include "GAM415_MainProjectCharacter.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
APortal::APortal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// **** Create the components for the portal
	mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	boxComp = CreateDefaultSubobject<UBoxComponent>("Box Comp");
	sceneCapture = CreateDefaultSubobject<USceneCaptureComponent2D>("Capture");
	// **** Create an arrow component to indicate the forward direction of the portal
	rootArrow = CreateDefaultSubobject<UArrowComponent>("Root Arrow");

	// **** Set the box component as the root component and attach the mesh and scene capture to it
	RootComponent = boxComp;
	mesh->SetupAttachment(boxComp);
	sceneCapture->SetupAttachment(mesh);
	rootArrow->SetupAttachment(RootComponent);

	// **** Disable collision so that the player can walk through the portal
	mesh->SetCollisionResponseToAllChannels(ECR_Ignore);
}

// Called when the game starts or when spawned
void APortal::BeginPlay()
{
	Super::BeginPlay();
	// **** Bind the overlap event to the OnOverlapBegin function
	boxComp->OnComponentBeginOverlap.AddDynamic(this, &APortal::OnOverlapBegin);
	mesh->SetHiddenInSceneCapture(true);
	//mesh->bCastStaticShadow(false);
	//mesh->bCastDynamicShadow(false);


	// **** Set the material of the mesh to the material specified in the editor, making illusion of a portal that is facing opposite of player
	if (mat)
	{
		mesh->SetMaterial(0, mat);
	}

}

// Called every frame
void APortal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdatePortals();

}

// **** Handle the overlap event, this will be called when the player overlaps with the portal
void APortal::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AGAM415_MainProjectCharacter* playerChar = Cast<AGAM415_MainProjectCharacter>(OtherActor);

	if (playerChar)
	{
		if (OtherPortal)
		{
			// **** Check if the player is not already teleporting, if not, set the boolean to true and teleport the player to the other portal's location
			if (!playerChar->isTeleporting)
			{
				playerChar->isTeleporting = true;
				FVector loc = OtherPortal->rootArrow->GetComponentLocation();
				playerChar->SetActorLocation(loc);


				FTimerHandle TimerHandle;
				FTimerDelegate TimerDelegate;
				TimerDelegate.BindUFunction(this, "SetBool", playerChar);
				GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, 1, false);
			}
		}
	}
}
// **** Set the boolean to false after 1 second to allow the player to teleport again
void APortal::SetBool(AGAM415_MainProjectCharacter* playerChar)
{
	if (playerChar)
	{
		playerChar->isTeleporting = false;
	}
}

// **** Update the scene capture component's location and rotation to match the player's camera, offset by the distance between the two portals
void APortal::UpdatePortals()
{
	FVector Location = this->GetActorLocation() - OtherPortal->GetActorLocation();
	FVector camLocation = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetTransformComponent()->GetComponentLocation();
	FRotator camRotation = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetTransformComponent()->GetComponentRotation();
	FVector CombinedLocation = camLocation + Location;

	sceneCapture->SetWorldLocationAndRotation(CombinedLocation, camRotation);

}

