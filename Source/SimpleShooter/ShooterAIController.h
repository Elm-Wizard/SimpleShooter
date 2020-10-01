// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ShooterAIController.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API AShooterAIController : public AAIController
{
	GENERATED_BODY()

public:
	// Poziva se svaki frejm
	virtual void Tick(float DeltaSeconds) override;
	bool IsDead() const;
	
protected:
	// Poziva se kada igra pocne ili se igrac spawnuje
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	class UBehaviorTree *AIBehavior; // Drvo ponasanja AI-a


};
