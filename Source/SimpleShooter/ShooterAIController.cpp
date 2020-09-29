// Fill out your copyright notice in the Description page of Project Settings.

#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"

// Poziva se kada igra pocne ili se igrac spawnuje
void AShooterAIController::BeginPlay() 
{
    Super::BeginPlay();
}

// Poziva se svaki frejm
void AShooterAIController::Tick(float DeltaTime) 
{
    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

    if (LineOfSightTo(PlayerPawn))
    {
        SetFocus(PlayerPawn); // Postavlja fokus AI-a na igraca
        MoveToActor(PlayerPawn, AcceptanceRadius); // Naredjuje AI-u da ide do igraca
    }
    else
    {
        ClearFocus(EAIFocusPriority::Gameplay); // Sklanja fokus sa igraca
        StopMovement(); // Zaustavlja kretanje AI-a
    }
    

}
