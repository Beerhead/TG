// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "C:\Users\Beerhead\Documents\TG\TestingGrounds\Source\TestingGrounds\TP_ThirdPerson\TP_ThirdPersonCharacter.h"
#include "PattrolingGuard.generated.h"

/**
 * 
 */
UCLASS()
class TESTINGGROUNDS_API APattrolingGuard : public ATP_ThirdPersonCharacter
{
	GENERATED_BODY()
	
	
public:
	UPROPERTY(EditInstanceOnly, Category = "Patrol Route")
		TArray<AActor*> PatrolPoints;

};
