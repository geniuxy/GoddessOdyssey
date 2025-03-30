// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/GoddessSurvivalGameMode.h"

#include "DebugHelper.h"
#include "NavigationSystem.h"
#include "Characters/Enemy.h"
#include "Engine/AssetManager.h"
#include "Engine/TargetPoint.h"
#include "Kismet/GameplayStatics.h"

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
			CurrentSpawnedEnemiesCounter += TrySpawnWaveEnemies();

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

	PreLoadNextWaveEnemiesMap.Empty();

	for (const FGoddessEnemyWaveSpawnerInfo& SpawnerInfo : GetCurrentWaveSpawnerTableRow()->EnemyWaveSpawnerDefinitions)
	{
		if (SpawnerInfo.SoftEnemyClassToSpawn.IsNull()) continue;

		UAssetManager::GetStreamableManager().RequestAsyncLoad(
			SpawnerInfo.SoftEnemyClassToSpawn.ToSoftObjectPath(),
			FStreamableDelegate::CreateLambda(
				[SpawnerInfo,this]()
				{
					if (UClass* LoadedClass = SpawnerInfo.SoftEnemyClassToSpawn.Get())
						PreLoadNextWaveEnemiesMap.Emplace(SpawnerInfo.SoftEnemyClassToSpawn, LoadedClass);
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

int32 AGoddessSurvivalGameMode::TrySpawnWaveEnemies()
{
	if (TargetPointsArray.IsEmpty())
		UGameplayStatics::GetAllActorsOfClass(this, ATargetPoint::StaticClass(), TargetPointsArray);
	checkf(!TargetPointsArray.IsEmpty(),
	       TEXT("No valid target point found in level: %s for spawning enemies"), *GetWorld()->GetName());

	uint32 EnemiesSpawnedThisTime = 0;

	FActorSpawnParameters SpawnParam;
	SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	for (const FGoddessEnemyWaveSpawnerInfo& SpawnerInfo : GetCurrentWaveSpawnerTableRow()->EnemyWaveSpawnerDefinitions)
	{
		if (SpawnerInfo.SoftEnemyClassToSpawn.IsNull()) continue;

		const int32 NumToSpawn = FMath::RandRange(SpawnerInfo.MinPerSpawnCount, SpawnerInfo.MaxPerSpawnCount);

		UClass* LoadedEnemyClass = PreLoadNextWaveEnemiesMap.FindChecked(SpawnerInfo.SoftEnemyClassToSpawn);

		for (int32 i = 0; i < NumToSpawn; i++)
		{
			const int32 RandomTargetPointIndex = FMath::RandRange(0, TargetPointsArray.Num() - 1);
			const FVector SpawnLocation = TargetPointsArray[RandomTargetPointIndex]->GetActorLocation();
			const FRotator SpawnRotator =
				TargetPointsArray[RandomTargetPointIndex]->GetActorForwardVector().ToOrientationRotator();

			FVector RandomLocation;
			UNavigationSystemV1::K2_GetRandomLocationInNavigableRadius(this, SpawnLocation, RandomLocation, 100.f);
			RandomLocation += FVector(0.f, 0.f, 150.f);

			AEnemy* SpawnEnemy = GetWorld()->SpawnActor<AEnemy>(LoadedEnemyClass, RandomLocation, SpawnRotator,
			                                                    SpawnParam);
			if (SpawnEnemy)
			{
				SpawnEnemy->OnDestroyed.AddUniqueDynamic(this, &ThisClass::OnEnemyDestroyed);

				EnemiesSpawnedThisTime++;
				TotalSpawnedEnemiesThisWaveCounter++;
			}

			if (!ShouldKeepSpawnEnemies())
				return EnemiesSpawnedThisTime;
		}
	}

	return EnemiesSpawnedThisTime;
}

bool AGoddessSurvivalGameMode::ShouldKeepSpawnEnemies() const
{
	return TotalSpawnedEnemiesThisWaveCounter < GetCurrentWaveSpawnerTableRow()->TotalEnemyToSpawnThisWave;
}

void AGoddessSurvivalGameMode::OnEnemyDestroyed(AActor* DestroyedActor)
{
	CurrentSpawnedEnemiesCounter--;

	Debug::Print(FString::Printf(TEXT("CurrentSpawnedEnemiesCounter: %i, TotalSpawnedEnemiesThisWaveCounter: %i"),
	                             CurrentSpawnedEnemiesCounter, TotalSpawnedEnemiesThisWaveCounter));

	if (ShouldKeepSpawnEnemies())
		CurrentSpawnedEnemiesCounter += TrySpawnWaveEnemies();
	else if (CurrentSpawnedEnemiesCounter == 0)
	{
		TotalSpawnedEnemiesThisWaveCounter = 0;
		CurrentSpawnedEnemiesCounter = 0;

		SetCurrentSurvivalGameModeState(EGoddessSurvivalGameModeState::WaveCompleted);
	}
}

void AGoddessSurvivalGameMode::RegisterSpawnedEnemies(const TArray<AEnemy*> InEnemiesToRegister)
{
	for (AEnemy* Enemy : InEnemiesToRegister)
	{
		if (Enemy)
		{
			CurrentSpawnedEnemiesCounter++;

			Enemy->OnDestroyed.AddUniqueDynamic(this, &ThisClass::OnEnemyDestroyed);
		}
	}
}
