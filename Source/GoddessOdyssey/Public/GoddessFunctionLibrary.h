// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GoddessTypes/GoddessEnumTypes.h"
#include "GoddessFunctionLibrary.generated.h"

struct FScalableFloat;
struct FGameplayTag;
class UBaseCombatComponent;
class UBaseAbilitySystemComponent;

/**
 * 
 */
UCLASS()
class GODDESSODYSSEY_API UGoddessFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static UBaseAbilitySystemComponent* NativeGetASCFromActor(AActor* InActor);

	UFUNCTION(BlueprintCallable, Category="FunctionLibrary")
	static void AddGameplayTagToActorIfNone(AActor* InActor, FGameplayTag TagToAdd);

	UFUNCTION(BlueprintCallable, Category="FunctionLibrary")
	static void RemoveGameplayTagFromActorIfFound(AActor* InActor, FGameplayTag TagToRemove);

	static bool NativeDoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck);

	// DisplayName允许你为函数提供一个更直观、更易读的名称，而不是直接使用函数的 C++ 名称。
	// ExpandEnumAsExecs它会为枚举中的每个值生成一个独立的执行分支
	UFUNCTION(BlueprintCallable, Category="FunctionLibrary",
		meta =(DisplayName = "Does Actor Have Tag", ExpandEnumAsExecs = "OutConfirmType"))
	static void BP_DoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck, EGoddessConfirmType& OutConfirmType);

	static UBaseCombatComponent* NativeGetCombatComponentFromActor(AActor* InActor);

	UFUNCTION(BlueprintCallable, Category="FunctionLibrary",
		meta =(DisplayName = "Get Combat Component From Actor", ExpandEnumAsExecs = "OutValidType"))
	static UBaseCombatComponent* BP_GetCombatComponentFromActor(AActor* InActor, EGoddessValidType& OutValidType);

	UFUNCTION(BlueprintCallable, Category="FunctionLibrary")
	static bool IsTargetPawnHostile(APawn* QueryPawn, APawn* TargetPawn);

	UFUNCTION(BlueprintPure, Category="FunctionLibrary", meta=(CompactNodeTitle="Get Value At Level"))
	static float GetScalableFloatValueAtLevel(const FScalableFloat& InScalableFloat, float InLevel = 1.0f);

	UFUNCTION(BlueprintPure, Category="FunctionLibrary")
	static FGameplayTag ComputeHitReactDirectionTag(AActor* InAttacker, AActor* InVictim, float& OutAngleDiff);
	
	UFUNCTION(BlueprintPure, Category="FunctionLibrary")
	static bool IsValidBlock(AActor* InAttacker, AActor* InDefender);
};
