// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Interfaces/CombatComponentInterface.h"
#include "Interfaces/UIComponentInterface.h"
#include "BaseCharacter.generated.h"

class UDataAsset_StartUpData;
class UBaseAttributeSet;
class UBaseAbilitySystemComponent;
class UMotionWarpingComponent;

UCLASS()
class GODDESSODYSSEY_API ABaseCharacter : public ACharacter, public IAbilitySystemInterface,
                                          public ICombatComponentInterface, public IUIComponentInterface
{
	GENERATED_BODY()

public:
	ABaseCharacter(const FObjectInitializer& ObjectInitializer);

	//~ Begin IAbilitySystemInterface Interface.
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	//~ End IAbilitySystemInterface Interface

	//~ Begin ICombatComponentInterface Interface.
	virtual UBaseCombatComponent* GetCombatComponentByInterface() const override;
	//~ End ICombatComponentInterface Interface

	//~ Begin IUIComponentInterface Interface.
	virtual UBaseUIComponent* GetUIComponentByInterface() const override;
	//~ End IUIComponentInterface Interface

protected:
	//~ Begin APawn Interface.
	virtual void PossessedBy(AController* NewController) override;
	//~ End APawn Interface

	int32 GetCurrentAbilityApplyLevel() const;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	UBaseAbilitySystemComponent* BaseAbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	UBaseAttributeSet* BaseAttributeSet;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MotionWarping")
	UMotionWarpingComponent* MotionWarpingComponent;
		
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CharacterData")
	TSoftObjectPtr<UDataAsset_StartUpData> CharacterStartUpData;

public:
	FORCEINLINE UBaseAbilitySystemComponent* GetBaseAbilitySystemComponent() const
	{
		return BaseAbilitySystemComponent;
	}

	FORCEINLINE UBaseAttributeSet* GetBaseAttributeSet() const { return BaseAttributeSet; }
};
