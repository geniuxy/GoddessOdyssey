// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BaseExtensionComponent.h"
#include "GoddessTypes/GoddessStructTypes.h"
#include "GoddessInventoryComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GODDESSODYSSEY_API UGoddessInventoryComponent : public UBaseExtensionComponent
{
	GENERATED_BODY()

public:
	UGoddessInventoryComponent();
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Inventory")
	FGoddessInventoryItemData InventoryItemData;
};
