// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "Enemy.generated.h"

class UEnemyUIComponent;
class UEnemyCombatComponent;
/**
 * 
 */
UCLASS()
class GODDESSODYSSEY_API AEnemy : public ABaseCharacter
{
	GENERATED_BODY()

public:
	AEnemy();

	//~ Begin ICombatComponentInterface Interface.
	virtual UBaseCombatComponent* GetCombatComponentByInterface() const override;
	//~ End ICombatComponentInterface Interface

	//~ Begin IUIComponentInterface Interface.
	virtual UBaseUIComponent* GetUIComponentByInterface() const override;
	virtual UEnemyUIComponent* GetEnemyUIComponentByInterface() const override;
	//~ End IUIComponentInterface Interface

protected:
	//~ Begin APawn Interface.
	virtual void PossessedBy(AController* NewController) override;
	//~ End APawn Interface
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Combat")
	UEnemyCombatComponent* EnemyCombatComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Combat")
	UEnemyUIComponent* EnemyUIComponent;

private:	
	void InitEnemyStartUpData();

public:
	FORCEINLINE UEnemyCombatComponent* GetEnemyCombatComponent() const { return EnemyCombatComponent; }
};
