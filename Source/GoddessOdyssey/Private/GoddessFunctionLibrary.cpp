// Fill out your copyright notice in the Description page of Project Settings.


#include "GoddessFunctionLibrary.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayTagContainer.h"
#include "GenericTeamAgentInterface.h"
#include "AbilitySystems/BaseAbilitySystemComponent.h"
#include "Interfaces/CombatComponentInterface.h"

UBaseAbilitySystemComponent* UGoddessFunctionLibrary::NativeGetASCFromActor(AActor* InActor)
{
	check(InActor);

	return Cast<UBaseAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(InActor));
}

void UGoddessFunctionLibrary::AddGameplayTagToActorIfNone(AActor* InActor, FGameplayTag TagToAdd)
{
	UBaseAbilitySystemComponent* ASC = NativeGetASCFromActor(InActor);

	if (!ASC->HasMatchingGameplayTag(TagToAdd))
		ASC->AddLooseGameplayTag(TagToAdd);
}

void UGoddessFunctionLibrary::RemoveGameplayTagFromActorIfFound(AActor* InActor, FGameplayTag TagToRemove)
{
	UBaseAbilitySystemComponent* ASC = NativeGetASCFromActor(InActor);

	if (ASC->HasMatchingGameplayTag(TagToRemove))
		ASC->RemoveLooseGameplayTag(TagToRemove);
}

bool UGoddessFunctionLibrary::NativeDoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck)
{
	UBaseAbilitySystemComponent* ASC = NativeGetASCFromActor(InActor);

	return ASC->HasMatchingGameplayTag(TagToCheck);
}

void UGoddessFunctionLibrary::BP_DoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck,
                                                  EGoddessConfirmType& OutConfirmType)
{
	OutConfirmType = NativeDoesActorHaveTag(InActor, TagToCheck) ? EGoddessConfirmType::Yes : EGoddessConfirmType::No;
}

UBaseCombatComponent* UGoddessFunctionLibrary::NativeGetCombatComponentFromActor(AActor* InActor)
{
	check(InActor);

	if (ICombatComponentInterface* CombatComponentInterface = Cast<ICombatComponentInterface>(InActor))
		return CombatComponentInterface->GetCombatComponentByInterface();
	return nullptr;
}

UBaseCombatComponent* UGoddessFunctionLibrary::BP_GetCombatComponentFromActor(
	AActor* InActor, EGoddessValidType& OutValidType)
{
	UBaseCombatComponent* CombatComponent = NativeGetCombatComponentFromActor(InActor);

	OutValidType = CombatComponent ? EGoddessValidType::Valid : EGoddessValidType::Invalid;

	return CombatComponent;
}

bool UGoddessFunctionLibrary::IsTargetPawnHostile(APawn* QueryPawn, APawn* TargetPawn)
{
	check(QueryPawn && TargetPawn);

	IGenericTeamAgentInterface* QueryTeamAgent = Cast<IGenericTeamAgentInterface>(QueryPawn->GetController());
	IGenericTeamAgentInterface* TargetTeamAgent = Cast<IGenericTeamAgentInterface>(TargetPawn->GetController());

	if (QueryTeamAgent && TargetTeamAgent)
		return QueryTeamAgent->GetGenericTeamId() != TargetTeamAgent->GetGenericTeamId();

	return false;
}
