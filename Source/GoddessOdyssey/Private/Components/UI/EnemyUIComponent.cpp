// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/UI/EnemyUIComponent.h"

#include "Widgets/BaseWidget.h"

void UEnemyUIComponent::RegisterEnemyDrawnWidget(UBaseWidget* InWidgetToRegister)
{
	EnemyDrawnWidgets.Add(InWidgetToRegister);
}

void UEnemyUIComponent::RemoveEnemyDrawnWidgetIfAny()
{
	if (EnemyDrawnWidgets.IsEmpty()) return;

	for (UBaseWidget* Widget : EnemyDrawnWidgets)
	{
		if (Widget)
			Widget->RemoveFromParent();
	}
}
