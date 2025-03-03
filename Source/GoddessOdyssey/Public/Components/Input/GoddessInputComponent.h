// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "DataAssets/Input/DataAsset_InputConfig.h"
#include "GoddessInputComponent.generated.h"

struct FGameplayTag;
class UDataAsset_InputConfig;
/**
 * 
 */
UCLASS()
class GODDESSODYSSEY_API UGoddessInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	template <class UserObject, typename CallbackFunc>
	void BindNativeInputAction(const UDataAsset_InputConfig* InInputConfig, const FGameplayTag& InInputTag,
	                           ETriggerEvent TriggerEvent, UserObject* ContextObject, CallbackFunc Func);

	template <class UserObject, typename CallbackFunc>
	void BindAbilityInputAction(const UDataAsset_InputConfig* InInputConfig, UserObject* ContextObject,
	                            CallbackFunc InputPressedFunc, CallbackFunc InputReleasedFunc);
};

template <class UserObject, typename CallbackFunc>
void UGoddessInputComponent::BindNativeInputAction(const UDataAsset_InputConfig* InInputConfig,
                                                   const FGameplayTag& InInputTag, ETriggerEvent TriggerEvent,
                                                   UserObject* ContextObject, CallbackFunc Func)
{
	checkf(InInputConfig, TEXT("Input Data Asset is null, can not proceed with binding"));

	if (UInputAction* FoundAction = InInputConfig->FindNativeInputActionByTag(InInputTag))
		BindAction(FoundAction, TriggerEvent, ContextObject, Func);
}

template <class UserObject, typename CallbackFunc>
void UGoddessInputComponent::BindAbilityInputAction(const UDataAsset_InputConfig* InInputConfig,
                                                    UserObject* ContextObject, CallbackFunc InputPressedFunc,
                                                    CallbackFunc InputReleasedFunc)
{
	checkf(InInputConfig, TEXT("Input Data Asset is null, can not proceed with binding"));

	for (const FGoddessInputActionConfig& AbilityInputActionConfig : InInputConfig->AbilityInputActions)
	{
		if (!AbilityInputActionConfig.IsValid()) continue;

		BindAction(AbilityInputActionConfig.InputAction, ETriggerEvent::Started, ContextObject, InputPressedFunc,
		           AbilityInputActionConfig.InputTag);
		BindAction(AbilityInputActionConfig.InputAction, ETriggerEvent::Completed, ContextObject, InputReleasedFunc,
		           AbilityInputActionConfig.InputTag);
	}
}
