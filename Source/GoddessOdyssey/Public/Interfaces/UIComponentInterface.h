// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "UIComponentInterface.generated.h"

class UEnemyUIComponent;
class UBaseUIComponent;
class UGoddessUIComponent;
// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UUIComponentInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GODDESSODYSSEY_API IUIComponentInterface
{
	GENERATED_BODY()

public:
	virtual UBaseUIComponent* GetUIComponentByInterface() const = 0;
	virtual UGoddessUIComponent* GetGoddessUIComponentByInterface() const;
	virtual UEnemyUIComponent* GetEnemyUIComponentByInterface() const;
};
