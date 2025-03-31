// Fill out your copyright notice in the Description page of Project Settings.


#include "GoddessGameInstance.h"

TSoftObjectPtr<UWorld> UGoddessGameInstance::GetGameLevelByTag(FGameplayTag InTag) const
{
	for (const FGoddessGameLevelSet& GameLevelSet : GameLevelSets)
	{
		if (!GameLevelSet.IsValid()) continue;

		if (GameLevelSet.LevelTag == InTag)
			return GameLevelSet.Level;
	}
	return TSoftObjectPtr<UWorld>();
}
