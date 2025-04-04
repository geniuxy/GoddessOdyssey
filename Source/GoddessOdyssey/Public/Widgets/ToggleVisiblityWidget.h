// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseWidget.h"
#include "ToggleVisiblityWidget.generated.h"

/**
 * 
 */
UCLASS()
class GODDESSODYSSEY_API UToggleVisiblityWidget : public UBaseWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	void PlayFadeIn();
	void PlayFadeOut();
	void PlayFadeAnimation(UWidgetAnimation* WidgetAnimation, EUMGSequencePlayMode::Type InPlayMode);

	void SetTimer(float Duration, FTimerDelegate TimerDelegate);

	UFUNCTION(BlueprintCallable)
	void OnPickupMoney();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	float FadeOutDuration = 5.0f;
	
private:
	// fadeIn 动画
	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* FadeInAnimation;

	// 定时器句柄
	FTimerHandle FadeOutTimerHandle;

	bool bIsFadeIn = false;
};
