// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GoddessTypes/GoddessEnumTypes.h"
#include "BaseGameplayAbility.generated.h"

class UBaseAbilitySystemComponent;
class UBaseCombatComponent;

UENUM(BlueprintType)
enum class EBaseAbilityActivationPolicy:uint8
{
	OnTrigger,
	OnGiven
};

/**
 * 
 */
UCLASS()
class GODDESSODYSSEY_API UBaseGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

protected:
	//~ Begin UGameplayAbility Interface.
	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle,
	                        const FGameplayAbilityActorInfo* ActorInfo,
	                        const FGameplayAbilityActivationInfo ActivationInfo,
	                        bool bReplicateEndAbility,
	                        bool bWasCancelled) override;
	//~ End UGameplayAbility Interface

	UPROPERTY(EditDefaultsOnly, Category="BaseAbility")
	EBaseAbilityActivationPolicy AbilityActivationPolicy = EBaseAbilityActivationPolicy::OnTrigger;

	// BlueprintPure 函数不会显示执行引脚（白色引脚）
	// BlueprintPure 函数必须有返回值或输出参数
	UFUNCTION(BlueprintPure, Category="BaseAbility")
	UBaseCombatComponent* GetBaseCombatComponentFromActorInfo() const;

	UFUNCTION(BlueprintPure, Category="BaseAbility")
	UBaseAbilitySystemComponent* GetBaseAbilitySystemComponentFromActorInfo() const;

	FActiveGameplayEffectHandle NativeApplyEffectSpecHandleToTarget(AActor* TargetActor,
	                                                                const FGameplayEffectSpecHandle& InSpecHandle);

	UFUNCTION(BlueprintCallable, Category="BaseAbility",
		meta=(DisplayName = "Apply Effect Spec Handle To Target", ExpandEnumAsExecs = "OutSuccessType"))
	FActiveGameplayEffectHandle BP_ApplyEffectSpecHandleToTarget(AActor* TargetActor,
	                                                             const FGameplayEffectSpecHandle& InSpecHandle,
	                                                             EGoddessSuccessType& OutSuccessType);

	UFUNCTION(BlueprintCallable, Category="BaseAbility")
	void ApplyGameplayEffectSpecHandleToHitResults(const FGameplayEffectSpecHandle& InSpecHandle,
	                                               const TArray<FHitResult>& InHitResults);
};
