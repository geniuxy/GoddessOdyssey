// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/UI/GoddessUIComponent.h"

#include "Blueprint/UserWidget.h"
#include "PlayerControllers/GoddessController.h"
#include "Widgets/BaseWidget.h"

void UGoddessUIComponent::DrawMainWidget()
{
	CachedMainWidget = CreateWidget<UBaseWidget>(GetOwningController<AGoddessController>(), MainWidgetClass);
	CachedMainWidget->AddToViewport();
}
