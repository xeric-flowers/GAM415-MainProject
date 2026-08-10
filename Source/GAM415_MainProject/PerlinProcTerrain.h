// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PerlinProcTerrain.generated.h"

// *** Forward declarations so we don't have to include the headers for these classes in this header file
class UProceduralMeshComponent;
class UMaterialInterface;

UCLASS()
class GAM415_MAINPROJECT_API APerlinProcTerrain : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APerlinProcTerrain();

	// *** all the properties for the procedural mesh, including size, scale, and material

	UPROPERTY(EditAnywhere, Meta = (ClampMin = 0))
	int XSize = 0;

	UPROPERTY(EditAnywhere, Meta = (ClampMin = 0))
	int YSize = 0;

	// *** ZMultiplier is used to scale the height of the terrain, and is clamped to a minimum of 0 to prevent negative scaling
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ClampMin = 0))
	float ZMultiplier = 1.0f;

	// *** NoiseScale is used to scale the Perlin noise
	UPROPERTY(EditAnywhere, Meta = (ClampMin = 0))
	float NoiseScale = 1.0f;

	// *** Controls the spacing of each vertex
	UPROPERTY(EditAnywhere, Meta = (CLampMin = 0.000001))
	float Scale = 0;

	// *** Controls the scale of the UVs
	UPROPERTY(EditAnywhere, Meta = (CLampMin = 0.000001))
	float UVScale = 0;

	// *** Controls the radius of the impact point of the projectile
	UPROPERTY(EditAnywhere)
	float radius;

	// *** Controls the depth of the impact point of the projectile
	UPROPERTY(EditAnywhere)
	FVector Depth;




protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// *** Material for the procedural mesh, which can be set in the editor
	UPROPERTY(EditAnywhere)
	UMaterialInterface* Mat;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// *** Alters the procedural mesh based on the impact point of the projectile
	UFUNCTION()
	void AlterMesh(FVector impactPoint);

private:
	// *** Procedural mesh component that will be used to create the terrain
	UProceduralMeshComponent* ProcMesh;
	// *** Arrays to hold the vertices, triangles, UVs, normals, and vertex colors for the procedural mesh
	TArray<FVector> Vertices;
	TArray<int> Triangles;
	TArray<FVector2D> UV0;
	TArray<FVector> Normals;
	TArray<FColor> UpVertexColors;

	// *** Section ID for the procedural mesh, which is used to identify the mesh section when updating it, may be used in future
	int sectionID = 0;

	// *** Functions to create the vertices and triangles for the procedural mesh
	void CreateVertices();
	void CreateTriangles();
};
