// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystems/AbilityTasks/AbilityTask_WaitSpawnEnemies.h"

#include "AbilitySystemComponent.h"
#include "NavigationSystem.h"
#include "Characters/Enemy.h"
#include "Engine/AssetManager.h"

UAbilityTask_WaitSpawnEnemies* UAbilityTask_WaitSpawnEnemies::WaitSpawnEnemies(
	UGameplayAbility* OwningAbility,
	FGameplayTag EventTag,
	TSoftClassPtr<AEnemy> SoftEnemyClassToSpawn,
	int32 NumToSpawn,
	const FVector& SpawnOrigin,
	float RandomSpawnRadius)
{
	UAbilityTask_WaitSpawnEnemies* Node = NewAbilityTask<UAbilityTask_WaitSpawnEnemies>(OwningAbility);

	Node->CachedEventTag = EventTag;
	Node->CachedSoftEnemyClassToSpawn = SoftEnemyClassToSpawn;
	Node->CachedNumToSpawn = NumToSpawn;
	Node->CachedSpawnOrigin = SpawnOrigin;
	Node->CachedRandomSpawnRadius = RandomSpawnRadius;

	return Node;
}

void UAbilityTask_WaitSpawnEnemies::Activate()
{
	// 加个引用，确保Activate()和OnDestroy()中调用的是同一个Delegate
	FGameplayEventMulticastDelegate& Delegate =
		AbilitySystemComponent->GenericGameplayEventCallbacks.FindOrAdd(CachedEventTag);

	DelegateHandle = Delegate.AddUObject(this, &ThisClass::OnGameplayEventReceived);
}

void UAbilityTask_WaitSpawnEnemies::OnDestroy(bool bInOwnerFinished)
{
	// 加个引用，确保Activate()和OnDestroy()中调用的是同一个Delegate
	FGameplayEventMulticastDelegate& Delegate =
		AbilitySystemComponent->GenericGameplayEventCallbacks.FindOrAdd(CachedEventTag);

	Delegate.Remove(DelegateHandle);

	Super::OnDestroy(bInOwnerFinished);
}

void UAbilityTask_WaitSpawnEnemies::OnGameplayEventReceived(const FGameplayEventData* InPayload)
{
	if (ensure(!CachedSoftEnemyClassToSpawn.IsNull()))
	{
		UAssetManager::Get().GetStreamableManager().RequestAsyncLoad(
			CachedSoftEnemyClassToSpawn.ToSoftObjectPath(),
			FStreamableDelegate::CreateUObject(this, &ThisClass::OnEnemyClassLoaded)
		);
	}
	else
	{
		if (ShouldBroadcastAbilityTaskDelegates())
			DidNotSpawn.Broadcast(TArray<AEnemy*>());

		EndTask();
	}
}

void UAbilityTask_WaitSpawnEnemies::OnEnemyClassLoaded()
{
	UClass* LoadClass = CachedSoftEnemyClassToSpawn.Get();
	UWorld* World = GetWorld();

	if (!LoadClass || !World)
	{
		if (ShouldBroadcastAbilityTaskDelegates())
			DidNotSpawn.Broadcast(TArray<AEnemy*>());

		EndTask();
		return;
	}

	TArray<AEnemy*> SpawnEnemies;
	
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	for (int32 i = 0; i < CachedNumToSpawn; i++)
	{
		FVector RandomLocation;
		UNavigationSystemV1::K2_GetRandomReachablePointInRadius(
			this,
			CachedSpawnOrigin,
			RandomLocation,
			CachedRandomSpawnRadius
		);
		// 为了不让生成的敌人在地里
		RandomLocation += FVector(0.f, 0.f, 150.f);

		const FRotator SpawnFacingRotation =
			AbilitySystemComponent->GetAvatarActor()->GetActorForwardVector().ToOrientationRotator();

		AEnemy* SpawnEnemy = World->SpawnActor<AEnemy>(LoadClass, RandomLocation, SpawnFacingRotation, SpawnParameters);
		if (SpawnEnemy)
			SpawnEnemies.Add(SpawnEnemy);
	}

	if (ShouldBroadcastAbilityTaskDelegates())
	{
		if (!SpawnEnemies.IsEmpty())
			OnSpawnFinished.Broadcast(SpawnEnemies);
		else
			DidNotSpawn.Broadcast(TArray<AEnemy*>());
	}

	EndTask();
}
