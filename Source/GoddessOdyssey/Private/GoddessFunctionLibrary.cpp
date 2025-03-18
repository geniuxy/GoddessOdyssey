// Fill out your copyright notice in the Description page of Project Settings.


#include "GoddessFunctionLibrary.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "DebugHelper.h"
#include "GameplayTagContainer.h"
#include "GenericTeamAgentInterface.h"
#include "GoddessGameplayTags.h"
#include "AbilitySystems/BaseAbilitySystemComponent.h"
#include "Interfaces/CombatComponentInterface.h"
#include "Kismet/KismetMathLibrary.h"

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

float UGoddessFunctionLibrary::GetScalableFloatValueAtLevel(const FScalableFloat& InScalableFloat, float InLevel)
{
	return InScalableFloat.GetValueAtLevel(InLevel);
}

FGameplayTag UGoddessFunctionLibrary::ComputeHitReactDirectionTag(AActor* InAttacker, AActor* InVictim,
                                                                  float& OutAngleDiff)
{
	check(InAttacker && InVictim);

	const FVector VictimForward = InVictim->GetActorForwardVector();
	const FVector VictimToAttackerNormalized =
		(InAttacker->GetActorLocation() - InVictim->GetActorLocation()).GetSafeNormal();

	const float DotResult = FVector::DotProduct(VictimForward, VictimToAttackerNormalized);
	OutAngleDiff = UKismetMathLibrary::DegAcos(DotResult);

	const FVector CrossResult = FVector::CrossProduct(VictimForward, VictimToAttackerNormalized);
	if (CrossResult.Z < 0)
		OutAngleDiff *= -1;

	if (OutAngleDiff >= -45.f && OutAngleDiff < 45.f)
		return GoddessGameplayTags::Shared_Status_HitReact_Front;
	if (OutAngleDiff >= -135.f && OutAngleDiff < -45.f)
		return GoddessGameplayTags::Shared_Status_HitReact_Left;
	if (OutAngleDiff >= 45.f && OutAngleDiff < 135.f)
		return GoddessGameplayTags::Shared_Status_HitReact_Right;
	if (OutAngleDiff < -135.f || OutAngleDiff > 135.f)
		return GoddessGameplayTags::Shared_Status_HitReact_Back;
	return GoddessGameplayTags::Shared_Status_HitReact_Front;
}

bool UGoddessFunctionLibrary::IsValidBlock(AActor* InAttacker, AActor* InDefender)
{
	check(InAttacker && InDefender);

	const float DotResult =
		FVector::DotProduct(InAttacker->GetActorForwardVector(), InDefender->GetActorForwardVector());
	// const FString result = FString::Printf(TEXT("Dot result: %f , %s"), DotResult,
	//                                        DotResult < -0.3f ? TEXT("Valid") : TEXT("Invalid"));
	//
	// Debug::Print(result, DotResult < -0.3f ? FColor::Green : FColor::Red);

	return DotResult < -0.3f;
}
