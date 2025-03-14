// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerControllers/GoddessController.h"

AGoddessController::AGoddessController()
{
	GoddessTeamId = FGenericTeamId(0);
}

FGenericTeamId AGoddessController::GetGenericTeamId() const
{
	return GoddessTeamId;
}
