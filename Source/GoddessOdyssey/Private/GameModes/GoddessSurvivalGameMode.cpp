// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/GoddessSurvivalGameMode.h"

void AGoddessSurvivalGameMode::BeginPlay()
{
	Super::BeginPlay();

	checkf(EnemyWaveSpawnerDataTable, TEXT("forget to assign a valid datatable in survival game mode"));

	TotalWavesToSpawn = EnemyWaveSpawnerDataTable->GetRowNames().Num();

	SetCurrentSurvivalGameModeState(EGoddessSurvivalGameModeState::WaitSpawnNewWave);
}

void AGoddessSurvivalGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (CurrentSurvivalGameModeState == EGoddessSurvivalGameModeState::WaitSpawnNewWave)
	{
		TimePassedSinceStart += DeltaSeconds;

		if (TimePassedSinceStart >= SpawnNewWaveWaitTime)
		{
			TimePassedSinceStart = 0.f;
			SetCurrentSurvivalGameModeState(EGoddessSurvivalGameModeState::SpawningNewWave);
		}
	}

	if (CurrentSurvivalGameModeState == EGoddessSurvivalGameModeState::SpawningNewWave)
	{
		TimePassedSinceStart += DeltaSeconds;

		if (TimePassedSinceStart >= SpawnEnemiesDelayTime)
		{
			// TODO: Handle Spawn New Enemies

			TimePassedSinceStart = 0.f;
			SetCurrentSurvivalGameModeState(EGoddessSurvivalGameModeState::InProgress);
		}
	}

	if (CurrentSurvivalGameModeState == EGoddessSurvivalGameModeState::WaveCompleted)
	{
		TimePassedSinceStart += DeltaSeconds;

		if (TimePassedSinceStart >= WaveCompleteWaitTime)
		{
			TimePassedSinceStart = 0.f;

			CurrentWaveCount++;

			if (HasFinishedAllWaves())
				SetCurrentSurvivalGameModeState(EGoddessSurvivalGameModeState::AllWaveDone);
			else
				SetCurrentSurvivalGameModeState(EGoddessSurvivalGameModeState::WaitSpawnNewWave);
		}
	}
}

void AGoddessSurvivalGameMode::SetCurrentSurvivalGameModeState(EGoddessSurvivalGameModeState InState)
{
	CurrentSurvivalGameModeState = InState;

	OnSurvivalGameModeStateChangedDelegate.Broadcast(CurrentSurvivalGameModeState);
}

bool AGoddessSurvivalGameMode::HasFinishedAllWaves() const
{
	return CurrentWaveCount > TotalWavesToSpawn;
}
