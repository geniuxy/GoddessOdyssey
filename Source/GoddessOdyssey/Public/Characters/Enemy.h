// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "Enemy.generated.h"

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

protected:
	//~ Begin APawn Interface.
	virtual void PossessedBy(AController* NewController) override;
	//~ End APawn Interface
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Combat")
	UEnemyCombatComponent* EnemyCombatComponent;

private:	
	void InitEnemyStartUpData();

public:
	FORCEINLINE UEnemyCombatComponent* GetEnemyCombatComponent() const { return EnemyCombatComponent; }
};
