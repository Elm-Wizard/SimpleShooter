// Fill out your copyright notice in the Description page of Project Settings.

#include "EngineUtils.h"
#include "GameFramework/Controller.h"
#include "ShooterAIController.h"
#include "KillThemAllGameMode.h"


void AKillThemAllGameMode::PawnKilled(APawn *PawnKilled) 
{
    Super::PawnKilled(PawnKilled);

    APlayerController *PlayerController = Cast<APlayerController>(PawnKilled->GetController());

    // Ako je igrac mrtav -> kraj igre
    if (PlayerController != nullptr)
    {
        EndGame(false); // Igrac nije pobedio
    }
    for (AShooterAIController *Controller : TActorRange<AShooterAIController>(GetWorld()))
    {
        if (!Controller->IsDead())
        {
            return;
        }
    }
    EndGame(true); // Igrac je pobedio
}

void AKillThemAllGameMode::EndGame(bool bIsPlayerWinner) 
{
    for(AController *Controller : TActorRange<AController>(GetWorld())) // Iterira kroz listu koji vraca sve kontrolere
    {
        bool bIsWinner = Controller->IsPlayerController() == bIsPlayerWinner; // Provera ako je AI pobednik ili igrac, shodno tome obavestava ostale aktere da je kraj igre
        Controller->GameHasEnded(Controller->GetPawn(), bIsWinner); // Prvi argument je da fokus i dalje bude na pobedniku
    } 
}
