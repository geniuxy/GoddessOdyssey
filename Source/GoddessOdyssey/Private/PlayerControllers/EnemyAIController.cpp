// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerControllers/EnemyAIController.h"

#include "DebugHelper.h"
#include "Navigation/CrowdFollowingComponent.h"

//FObjectInitializer：Unreal中用于初始化对象和子对象的工具，常见于构造函数中替换默认组件或修改属性。
//将默认的路径跟随组件（UPathFollowingComponent）替换为 支持群体行为（Crowd Avoidance）的组件（UCrowdFollowingComponent）
AEnemyAIController::AEnemyAIController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>("PathFollowingComponent"))
{
	if (UCrowdFollowingComponent* CrowdFollowingComponent = Cast<UCrowdFollowingComponent>(GetPathFollowingComponent()))
		Debug::Print(TEXT("Path Following Component Valid"), FColor::Green);
}
