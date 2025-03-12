// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/BaseWidget.h"

#include "Interfaces/UIComponentInterface.h"

void UBaseWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (IUIComponentInterface* UIComponentInterface = Cast<IUIComponentInterface>(GetOwningPlayerPawn()))
	{
		if (UGoddessUIComponent* GoddessUIComponent = UIComponentInterface->GetGoddessUIComponentByInterface())
			BP_OnOwningGoddessUIComponentInitialized(GoddessUIComponent);
	}
}
