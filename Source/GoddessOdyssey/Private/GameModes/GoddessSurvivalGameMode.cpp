// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/GoddessSurvivalGameMode.h"

#include "DebugHelper.h"
#include "Characters/Enemy.h"
#include "Engine/AssetManager.h"

void AGoddessSurvivalGameMode::BeginPlay()
{
	Super::BeginPlay();

	checkf(EnemyWaveSpawnerDataTable, TEXT("forget to assign a valid datatable in survival game mode"));

	TotalWavesToSpawn = EnemyWaveSpawnerDataTable->GetRowNames().Num();

	SetCurrentSurvivalGameModeState(EGoddessSurvivalGameModeState::WaitSpawnNewWave);

	PreLoadNextWaveEnemies();
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
			{
				SetCurrentSurvivalGameModeState(EGoddessSurvivalGameModeState::WaitSpawnNewWave);
				PreLoadNextWaveEnemies();
			}
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

void AGoddessSurvivalGameMode::PreLoadNextWaveEnemies()
{
	if (HasFinishedAllWaves()) return;
	
	for (const FGoddessEnemyWaveSpawnerInfo& SpawnerInfo : GetCurrentWaveSpawnerTableRow()->EnemyWaveSpawnerDefinitions)
	{
		if (SpawnerInfo.SoftEnemyClassToSpawn.IsNull()) continue;

		UAssetManager::GetStreamableManager().RequestAsyncLoad(
			SpawnerInfo.SoftEnemyClassToSpawn.ToSoftObjectPath(),
			FStreamableDelegate::CreateLambda(
				[SpawnerInfo,this]()
				{
					if (UClass* LoadedClass = SpawnerInfo.SoftEnemyClassToSpawn.Get())
					{
						PreLoadNextWaveEnemiesMap.Emplace(SpawnerInfo.SoftEnemyClassToSpawn, LoadedClass);

						Debug::Print(LoadedClass->GetName() + TEXT(" is loaded"));
					}
				}
			)
		);
	}
}

FGoddessEnemyWaveSpawnerTableRow* AGoddessSurvivalGameMode::GetCurrentWaveSpawnerTableRow() const
{
	const FName RowName = FName(TEXT("Wave") + FString::FromInt(CurrentWaveCount));

	FGoddessEnemyWaveSpawnerTableRow* FoundRow =
		EnemyWaveSpawnerDataTable->FindRow<FGoddessEnemyWaveSpawnerTableRow>(RowName, FString());

	checkf(FoundRow, TEXT("Could not find a valid row under the name %s in the data table"), *RowName.ToString());

	return FoundRow;
}
