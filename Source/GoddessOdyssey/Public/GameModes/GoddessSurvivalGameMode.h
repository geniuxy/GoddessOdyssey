// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GoddessGameMode.h"
#include "GoddessSurvivalGameMode.generated.h"


class AEnemy;

UENUM(BlueprintType)
enum class EGoddessSurvivalGameModeState:uint8
{
	WaitSpawnNewWave,
	SpawningNewWave,
	InProgress,
	WaveCompleted,
	AllWaveDone,
	PlayerDied
};

USTRUCT(BlueprintType)
struct FGoddessEnemyWaveSpawnerInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TSoftClassPtr<AEnemy> SoftEnemyClassToSpawn;

	UPROPERTY(EditAnywhere)
	int32 MinPerSpawnCount = 1;

	UPROPERTY(EditAnywhere)
	int32 MaxPerSpawnCount = 1;
};

USTRUCT(BlueprintType)
struct FGoddessEnemyWaveSpawnerTableRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TArray<FGoddessEnemyWaveSpawnerInfo> EnemyWaveSpawnerDefinitions;

	UPROPERTY(EditAnywhere)
	int32 TotalEnemyToSpawnThisWave = 1;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSurvivalGameModeStateChangedDelegate, EGoddessSurvivalGameModeState,
                                            CurrentState);

/**
 * 
 */
UCLASS()
class GODDESSODYSSEY_API AGoddessSurvivalGameMode : public AGoddessGameMode
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaSeconds) override;

protected:
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	virtual void BeginPlay() override;

private:
	void SetCurrentSurvivalGameModeState(EGoddessSurvivalGameModeState InState);
	bool HasFinishedAllWaves() const;
	void PreLoadNextWaveEnemies();
	FGoddessEnemyWaveSpawnerTableRow* GetCurrentWaveSpawnerTableRow() const;
	int32 TrySpawnWaveEnemies();
	bool ShouldKeepSpawnEnemies() const;

	UFUNCTION()
	void OnEnemyDestroyed(AActor* DestroyedActor);

	UFUNCTION(BlueprintCallable)
	void RegisterSpawnedEnemies(const TArray<AEnemy*> InEnemiesToRegister);

	UPROPERTY()
	EGoddessSurvivalGameModeState CurrentSurvivalGameModeState;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnSurvivalGameModeStateChangedDelegate OnSurvivalGameModeStateChangedDelegate;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="WaveDefinition", meta=(AllowPrivateAccess="true"))
	UDataTable* EnemyWaveSpawnerDataTable;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="WaveDefinition", meta=(AllowPrivateAccess="true"))
	int32 TotalWavesToSpawn;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="WaveDefinition", meta=(AllowPrivateAccess="true"))
	int32 CurrentWaveCount = 1;

	UPROPERTY()
	int32 CurrentSpawnedEnemiesCounter = 0;

	UPROPERTY()
	int32 TotalSpawnedEnemiesThisWaveCounter = 0;

	UPROPERTY()
	TArray<AActor*> TargetPointsArray;

	UPROPERTY()
	float TimePassedSinceStart = 0.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="WaveDefinition", meta=(AllowPrivateAccess="true"))
	float SpawnNewWaveWaitTime = 5.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="WaveDefinition", meta=(AllowPrivateAccess="true"))
	float SpawnEnemiesDelayTime = 2.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="WaveDefinition", meta=(AllowPrivateAccess="true"))
	float WaveCompleteWaitTime = 5.f;

	UPROPERTY()
	TMap<TSoftClassPtr<AEnemy>, UClass*> PreLoadNextWaveEnemiesMap;
};
