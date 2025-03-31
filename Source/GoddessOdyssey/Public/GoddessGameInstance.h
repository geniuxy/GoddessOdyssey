// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/GameInstance.h"
#include "GoddessGameInstance.generated.h"

USTRUCT(BlueprintType)
struct FGoddessGameLevelSet
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, meta=(Categories="GameData.Level"))
	FGameplayTag LevelTag;

	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<UWorld> Level;

	bool IsValid() const
	{
		return LevelTag.IsValid() && !Level.IsNull();
	}
};
/**
 * 
 */
UCLASS()
class GODDESSODYSSEY_API UGoddessGameInstance : public UGameInstance
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FGoddessGameLevelSet> GameLevelSets;
	
private:
	UFUNCTION(BlueprintPure, meta=(GameplayTagFilter ="GameData.Level"))
	TSoftObjectPtr<UWorld> GetGameLevelByTag(FGameplayTag InTag) const;
};
