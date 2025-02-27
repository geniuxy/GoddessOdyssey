// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "BaseCharacter.generated.h"

class UBaseAttributeSet;
class UBaseAbilitySystemComponent;

UCLASS()
class GODDESSODYSSEY_API ABaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ABaseCharacter();

	//~ Begin IAbilitySystemInterface Interface.
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	//~ End IAbilitySystemInterface Interface

protected:
	//~ Begin APawn Interface.
	virtual void PossessedBy(AController* NewController) override;
	//~ End APawn Interface

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	UBaseAbilitySystemComponent* BaseAbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	UBaseAttributeSet* BaseAttributeSet;

public:
	FORCEINLINE UBaseAbilitySystemComponent* GetBaseAbilitySystemComponent() const
	{
		return BaseAbilitySystemComponent;
	}

	FORCEINLINE UBaseAttributeSet* GetBaseAttributeSet() const { return BaseAttributeSet; }
};
