// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

UCLASS()
class TESTINGGROUNDS_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void CreateGrass();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BluePrintCallable, Category = "Terrain")
	void PlaceActors(TSubclassOf<AActor> ActorToSpawn, int MinSpawn=1, int MaxSpawn=1, float Radius=400, float MinScale = 1, float MaxScale = 1);

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Terrain)
	UPROPERTY(Category = Terrain, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UHierarchicalInstancedStaticMeshComponent* HISMC;

	UPROPERTY(Category = Terrain, EditAnywhere, BlueprintReadWrite)
		int32 QuantityGrassInstances = 100;

private:
	bool IsCanSpawnInLocation(FVector Location, float Radius);
	bool GetEmptyPlace(FVector& CandidateLocation, float Radius);
	void PlaceActor(TSubclassOf<AActor> ActorToSpawn, FVector PlaceToSpawn, float Rotation, float Scale);
};


