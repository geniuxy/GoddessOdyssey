// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

enum class EGoddesssCountDownActionOutput : uint8;

class FGoddessCountDownAction : public FPendingLatentAction
{
public:
	FGoddessCountDownAction(float InTotalCountDownTime, float InUpdateInterval, float& InOutRemainingTime,
	                        EGoddesssCountDownActionOutput& InCountDownOutput, const FLatentActionInfo& LatentInfo)
		: bNeedToCancel(false)
		  , TotalCountDownTime(InTotalCountDownTime)
		  , UpdateInterval(InUpdateInterval)
		  , OutRemainingTime(InOutRemainingTime)
		  , CountDownOutput(InCountDownOutput)
		  , ExecutionFunction(LatentInfo.ExecutionFunction)
		  , OutputLink(LatentInfo.Linkage)
		  , CallbackTarget(LatentInfo.CallbackTarget)
		  , ElapsedInterval(0.f)
		  , ElapsedTimeSinceStart(0.f)
	{
	}

	virtual void UpdateOperation(FLatentResponse& Response) override;

	void CancelAction();

private:
	bool bNeedToCancel;
	float TotalCountDownTime;
	float UpdateInterval; // 更新间隔
	float& OutRemainingTime;
	EGoddesssCountDownActionOutput& CountDownOutput;
	FName ExecutionFunction;
	int32 OutputLink;
	FWeakObjectPtr CallbackTarget;
	float ElapsedInterval; // 已用时间间隔
	float ElapsedTimeSinceStart;  // 已用时间
};
