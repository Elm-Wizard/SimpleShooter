// Fill out your copyright notice in the Description page of Project Settings.

#include "TimerManager.h"
#include "Blueprint/UserWidget.h"
#include "ShooterPlayerController.h"

void AShooterPlayerController::GameHasEnded(class AActor *EndGameFocus, bool bIsWinner)
{
    Super::GameHasEnded(EndGameFocus, bIsWinner);

    if (bIsWinner)
    {
        // Instanciramo win screen
        UUserWidget *WinScreen = CreateWidget(this, WinScreenClass);
        if (WinScreen != nullptr)
        {
            WinScreen->AddToViewport(); // Prikaz lose screena
        }
    }
    else
    {
        // Instanciramo lose screen
        UUserWidget *LoseScreen = CreateWidget(this, LoseScreenClass);
        if (LoseScreen != nullptr)
        {
            LoseScreen->AddToViewport(); // Prikaz lose screena
        }
    }
    // Restartuje nivo na tajmeru
    GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, RestartDelay);
}
