// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "GoddessTypes/GoddessEnumTypes.h"
#include "GoddessSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class GODDESSODYSSEY_API UGoddessSaveGame : public USaveGame
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly)
	EGoddessGameDifficulty SavedCurrentGameDifficulty;
};
