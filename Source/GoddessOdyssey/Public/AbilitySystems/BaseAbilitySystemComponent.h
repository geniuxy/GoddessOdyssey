// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "BaseAbilitySystemComponent.generated.h"

struct FGoddessAbilitySet;
/**
 * 
 */
UCLASS()
class GODDESSODYSSEY_API UBaseAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	void OnAbilityInputPressed(const FGameplayTag& InInputTag);
	void OnAbilityInputReleased(const FGameplayTag& InInputTag);

	UFUNCTION(BlueprintCallable, Category="Ability", meta=(ApplyLevel = "1"))
	void GrantGoddessWeaponAbilities(const TArray<FGoddessAbilitySet>& InAbilitiesToGrant, int32 ApplyLevel,
	                                 TArray<FGameplayAbilitySpecHandle>& OutGrantedAbilitySpecHandles);

	//在 C++ 中，函数参数默认是值传递（除非明确指定为引用或指针）。
	//通过 UPARAM(ref)，你可以将参数标记为引用传递，这样在蓝图中调用该函数时，蓝图可以传递一个变量的引用，而不是复制该变量的值。
	UFUNCTION(BlueprintCallable, Category="Ability")
	void RemoveGrantedGoddessWeaponAbilities(UPARAM(ref) TArray<FGameplayAbilitySpecHandle>& InSpecHandlesToRemove);
};
