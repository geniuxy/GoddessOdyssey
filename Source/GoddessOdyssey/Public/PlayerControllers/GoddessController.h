// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GenericTeamAgentInterface.h"
#include "GameFramework/PlayerController.h"
#include "GoddessController.generated.h"

/**
 * 
 */
UCLASS()
class GODDESSODYSSEY_API AGoddessController : public APlayerController, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	AGoddessController();
protected:
	//~ Begin IGenericTeamAgentInterface Interface.
	virtual FGenericTeamId GetGenericTeamId() const;
	//~ End IGenericTeamAgentInterface Interface

private:
	FGenericTeamId GoddessTeamId;
};
