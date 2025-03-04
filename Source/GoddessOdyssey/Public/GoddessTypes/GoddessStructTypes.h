// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GoddessStructTypes.generated.h"

class UGoddessLinkedAnimLayer;

USTRUCT(BlueprintType)
struct FGoddessWeaponData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGoddessLinkedAnimLayer> WeaponAnimLayerToLink;
};
