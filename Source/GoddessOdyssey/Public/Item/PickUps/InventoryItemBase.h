// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickUpBase.h"
#include "InventoryItemBase.generated.h"

UCLASS()
class GODDESSODYSSEY_API AInventoryItemBase : public APickUpBase
{
	GENERATED_BODY()

public:
	void AddToInventory(UDataTable* AllInventoryItemsDataTable, FGoddessInventoryItemData& InventoryItemData);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Data Table|Pick Up")
	FGoddessSlotData InventoryItemSlotData;

	bool TryAddItemToInventory(FGoddessSlotData& GoddessSlotData, TArray<FGoddessSlotData>& InGroup,
	                           int32 InMaxGroupSlotSize);

	virtual void OnPickUpCollisionSphereBeginOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	) override;

private:
	int32 CachedFoundItemsStackSize = -1;
};
