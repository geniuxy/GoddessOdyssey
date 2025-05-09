// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/UI/BaseUIComponent.h"
#include "EnemyUIComponent.generated.h"

class UBaseWidget;
/**
 * 
 */
UCLASS()
class GODDESSODYSSEY_API UEnemyUIComponent : public UBaseUIComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void RegisterEnemyDrawnWidget(UBaseWidget* InWidgetToRegister);

	UFUNCTION(BlueprintCallable)
	void RemoveEnemyDrawnWidgetIfAny();

private:
	TArray<UBaseWidget*> EnemyDrawnWidgets;
};
