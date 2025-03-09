// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CombatComponentInterface.generated.h"

class UBaseCombatComponent;

UINTERFACE(MinimalAPI)
class UCombatComponentInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GODDESSODYSSEY_API ICombatComponentInterface
{
	GENERATED_BODY()

public:
	virtual UBaseCombatComponent* GetCombatComponentByInterface() const = 0;
};
