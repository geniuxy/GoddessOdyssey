// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/UI/BaseUIComponent.h"
#include "GoddessUIComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEquippedWeaponChanged, TSoftObjectPtr<UTexture2D>, SoftWeaponIcon);

/**
 * 
 */
UCLASS()
class GODDESSODYSSEY_API UGoddessUIComponent : public UBaseUIComponent
{
	GENERATED_BODY()

public:
	// BlueprintAssignable 是虚幻引擎中用于 C++ 属性的修饰符，主要用于将多播委托（Multicast Delegate）暴露给蓝图
	UPROPERTY(BlueprintAssignable)
	FOnPercentChangedDelegate OnCurrentRageChanged;
	
	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FOnEquippedWeaponChanged OnEquippedWeaponChanged;
};
