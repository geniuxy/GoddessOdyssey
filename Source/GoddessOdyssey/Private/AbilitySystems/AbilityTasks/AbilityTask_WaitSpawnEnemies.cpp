// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystems/AbilityTasks/AbilityTask_WaitSpawnEnemies.h"

#include "AbilitySystemComponent.h"
#include "DebugHelper.h"

UAbilityTask_WaitSpawnEnemies* UAbilityTask_WaitSpawnEnemies::WaitSpawnEnemies(
	UGameplayAbility* OwningAbility,
	FGameplayTag EventTag,
	TSoftClassPtr<AEnemy> SoftEnemyClassToSpawn,
	int32 NumToSpawn,
	const FVector& SpawnOrigin,
	float RandomSpawnRadius,
	const FRotator& SpawnRotation)
{
	UAbilityTask_WaitSpawnEnemies* Node = NewAbilityTask<UAbilityTask_WaitSpawnEnemies>(OwningAbility);

	Node->CachedEventTag = EventTag;
	Node->CachedSoftEnemyClassToSpawn = SoftEnemyClassToSpawn;
	Node->CachedNumToSpawn = NumToSpawn;
	Node->CachedSpawnOrigin = SpawnOrigin;
	Node->CachedRandomSpawnRadius = RandomSpawnRadius;
	Node->CachedSpawnRotation = SpawnRotation;

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
	Debug::Print(TEXT("Summon Enemies Ability Activate"));

	EndTask();
}
