
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../TestingGroundsGameMode.h"
#include "InfiniteTerrainGameMode.generated.h"
class UActorPool;

/**
 * 
 */
UCLASS()
class TESTINGGROUNDS_API AInfiniteTerrainGameMode : public ATestingGroundsGameMode
{
	GENERATED_BODY()
	
		AInfiniteTerrainGameMode();

	void AddToPool(AVolume* VolumeToAdd);

	void StartPlay() override;
public:
	UFUNCTION(BlueprintCallable)
	void PopulateBoundVolumePool();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = NavMeshValueVolume)
	UActorPool* NavMeshPool;
};
