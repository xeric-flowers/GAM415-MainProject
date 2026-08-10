// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SceneCaptureComponent2D.h"	// ****
#include "Engine/TextureRenderTarget2D.h"		// **** 
#include "Components/BoxComponent.h"			// **** 
#include "Portal.generated.h"					

// **** Add forward declaration to access the player character class
class GAM415_MainProjectCharacter;

UCLASS()
class GAM415_MAINPROJECT_API APortal : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APortal();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// **** Add a function to handle the overlap event, this will be called when the player overlaps with the portal
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USceneCaptureComponent2D* sceneCapture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTextureRenderTarget2D* renderTarget;

	
	UPROPERTY(EditAnywhere)
		UBoxComponent* boxComp;

	UPROPERTY(EditAnywhere)
		APortal* OtherPortal;

	UPROPERTY(EditAnywhere)
		UMaterialInterface* mat;

	// **** Add a boolean to check if the player is overlapping with the portal
	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void SetBool(AGAM415_MainProjectCharacter* playerChar);

	UFUNCTION()
		void UpdatePortals();











};
