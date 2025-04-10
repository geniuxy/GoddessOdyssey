// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BaseExtensionComponent.h"
#include "GoddessTypes/GoddessStructTypes.h"
#include "NPCInventoryComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GODDESSODYSSEY_API UNPCInventoryComponent : public UBaseExtensionComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="Inventory")
	void PrintSavedInventoryItemData();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Inventory")
	FGoddessInventoryItemData SavedInventoryItemData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Inventory")
	UDataTable* AllInventoryItemsDataTable;
};
