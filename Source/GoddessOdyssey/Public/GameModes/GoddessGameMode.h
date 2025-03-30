// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GoddessGameMode.generated.h"

enum class EGoddessGameDifficulty : uint8;
/**
 * 
 */
UCLASS()
class GODDESSODYSSEY_API AGoddessGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AGoddessGameMode();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Game Settings")
	EGoddessGameDifficulty CurrentGameDifficulty;

public:
	FORCEINLINE EGoddessGameDifficulty GetCurrentGameDifficulty() const { return CurrentGameDifficulty; }
};
