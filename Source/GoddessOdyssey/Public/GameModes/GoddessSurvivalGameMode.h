// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GoddessGameMode.h"
#include "GoddessSurvivalGameMode.generated.h"


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
	virtual void BeginPlay() override;

private:
	void SetCurrentSurvivalGameModeState(EGoddessSurvivalGameModeState InState);

	UPROPERTY()
	EGoddessSurvivalGameModeState CurrentSurvivalGameModeState;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnSurvivalGameModeStateChangedDelegate OnSurvivalGameModeStateChangedDelegate;
};
