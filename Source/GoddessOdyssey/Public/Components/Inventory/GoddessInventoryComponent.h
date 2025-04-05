// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BaseExtensionComponent.h"
#include "GoddessTypes/GoddessStructTypes.h"
#include "GoddessInventoryComponent.generated.h"


class UBaseWidget;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GODDESSODYSSEY_API UGoddessInventoryComponent : public UBaseExtensionComponent
{
	GENERATED_BODY()

public:
	// 打印SavedInventoryItemData中的所有数据
	UFUNCTION(BlueprintCallable, Category="Inventory")
	void PrintSavedInventoryItemData();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Inventory")
	TObjectPtr<UBaseWidget> CachedInventoryOverlay;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Inventory")
	FGoddessInventoryItemData SavedInventoryItemData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Inventory")
	UDataTable* AllInventoryItemsDataTable;

public:
	FORCEINLINE FGoddessInventoryItemData GetSavedInventoryItemData() const { return SavedInventoryItemData; }
	FORCEINLINE void SetSavedInventoryItemData(const FGoddessInventoryItemData& NewInventoryItemData)
	{
		SavedInventoryItemData = NewInventoryItemData;
	}
	FORCEINLINE UDataTable* GetAllInventoryItemsDataTable() const { return AllInventoryItemsDataTable; }
	FORCEINLINE void SetCachedInventoryOverlay(UBaseWidget* NewInventoryOverlay)
	{
		CachedInventoryOverlay = NewInventoryOverlay;
	}
};
