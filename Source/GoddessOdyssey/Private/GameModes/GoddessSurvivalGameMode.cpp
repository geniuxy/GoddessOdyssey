// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/GoddessSurvivalGameMode.h"

void AGoddessSurvivalGameMode::BeginPlay()
{
	Super::BeginPlay();
}

void AGoddessSurvivalGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AGoddessSurvivalGameMode::SetCurrentSurvivalGameModeState(EGoddessSurvivalGameModeState InState)
{
	CurrentSurvivalGameModeState = InState;

	OnSurvivalGameModeStateChangedDelegate.Broadcast(CurrentSurvivalGameModeState);
}
