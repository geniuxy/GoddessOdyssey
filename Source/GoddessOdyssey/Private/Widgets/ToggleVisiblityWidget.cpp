// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/ToggleVisiblityWidget.h"

#include "DebugHelper.h"
#include "Animation/WidgetAnimation.h"

void UToggleVisiblityWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UToggleVisiblityWidget::PlayFadeIn()
{
	if (FadeInAnimation)
		PlayFadeAnimation(FadeInAnimation, EUMGSequencePlayMode::Forward);
}

void UToggleVisiblityWidget::PlayFadeOut()
{
	if (FadeInAnimation)
		PlayFadeAnimation(FadeInAnimation, EUMGSequencePlayMode::Reverse);
}

void UToggleVisiblityWidget::PlayFadeAnimation(UWidgetAnimation* WidgetAnimation, EUMGSequencePlayMode::Type InPlayMode)
{
	if (WidgetAnimation)
		PlayAnimation(WidgetAnimation, 0.f, 1, InPlayMode, 1.f);
}

void UToggleVisiblityWidget::SetTimer(float Duration, FTimerDelegate TimerDelegate)
{
	GetWorld()->GetTimerManager().SetTimer(FadeOutTimerHandle, TimerDelegate, Duration, false);
}

void UToggleVisiblityWidget::OnPickupMoney()
{
	// 停止之前的定时器
	GetWorld()->GetTimerManager().ClearTimer(FadeOutTimerHandle);

	SetVisibility(ESlateVisibility::Visible);
	if (!bIsFadeIn)
	{
		// 播放 fadeIn 动画
		PlayFadeIn();
		bIsFadeIn = true;
	}

	// 设置定时器，5 秒后播放 fadeOut 动画
	GetWorld()->GetTimerManager().SetTimer(FadeOutTimerHandle, [this]()
	{
		PlayFadeOut();
		bIsFadeIn = false;
	}, FadeOutDuration, false);
}
