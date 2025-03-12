// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BaseWidget.generated.h"

class UGoddessUIComponent;
/**
 * 
 */
UCLASS()
class GODDESSODYSSEY_API UBaseWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized() override;

	UFUNCTION(BlueprintImplementableEvent, meta= (DisplayName = "On Owning Goddess UI Component Initialized"))
	void BP_OnOwningGoddessUIComponentInitialized(UGoddessUIComponent* GoddessUIComponent);
};
