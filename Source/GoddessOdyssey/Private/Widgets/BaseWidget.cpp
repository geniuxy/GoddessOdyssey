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

void UBaseWidget::InitEnemyCreatedWidget(AActor* OwningEnemyActor)
{
	if (IUIComponentInterface* UIComponentInterface = Cast<IUIComponentInterface>(OwningEnemyActor))
	{
		UEnemyUIComponent* EnemyUIComponent = UIComponentInterface->GetEnemyUIComponentByInterface();

		checkf(EnemyUIComponent,
		       TEXT("Failed to extrac an EnemyUIComponent from %s"), *OwningEnemyActor->GetActorNameOrLabel());

		BP_OnOwningEnemyUIComponentInitialized(EnemyUIComponent);
	}
}
