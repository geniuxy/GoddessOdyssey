// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerControllers/EnemyAIController.h"

#include "DebugHelper.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Navigation/CrowdFollowingComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

//FObjectInitializer：Unreal中用于初始化对象和子对象的工具，常见于构造函数中替换默认组件或修改属性。
//将默认的路径跟随组件（UPathFollowingComponent）替换为 支持群体行为（Crowd Avoidance）的组件（UCrowdFollowingComponent）
AEnemyAIController::AEnemyAIController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>("PathFollowingComponent"))
{
	// if (UCrowdFollowingComponent* CrowdFollowingComponent = Cast<UCrowdFollowingComponent>(GetPathFollowingComponent()))
	// 	Debug::Print(TEXT("Path Following Component Valid"), FColor::Green);

	EnemySenseConfig_Sight = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("EnemySenseConfig_Sight"));
	EnemySenseConfig_Sight->DetectionByAffiliation.bDetectEnemies = true;
	EnemySenseConfig_Sight->DetectionByAffiliation.bDetectFriendlies = false;
	EnemySenseConfig_Sight->DetectionByAffiliation.bDetectNeutrals = false;
	EnemySenseConfig_Sight->SightRadius = 5000.f; // 能够看到目标的最大距离
	EnemySenseConfig_Sight->LoseSightRadius = 0.f; // 失去目标视野的距离
	EnemySenseConfig_Sight->PeripheralVisionAngleDegrees = 360.f; // 设置 AI 的视野角度

	EnemyPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("EnemyPerceptionComponent"));
	// ConfigureSense 将视觉感知配置（EnemySenseConfig_Sight）应用到感知组件中，使 AI 控制器具备视觉感知能力。
	EnemyPerceptionComponent->ConfigureSense(*EnemySenseConfig_Sight);
	// SetDominantSense 设置视觉感知（UAISenseConfig_Sight）为主要的感知方式。
	EnemyPerceptionComponent->SetDominantSense(UAISenseConfig_Sight::StaticClass());
	EnemyPerceptionComponent->OnTargetPerceptionUpdated.AddUniqueDynamic(
		this, &AEnemyAIController::OnEnemyPerceptionUpdated);

	Super::SetGenericTeamId(FGenericTeamId(1));
}

ETeamAttitude::Type AEnemyAIController::GetTeamAttitudeTowards(const AActor& Other) const
{
	const APawn* PawnToCheck = Cast<const APawn>(&Other);

	const IGenericTeamAgentInterface* OtherTeamAgent = Cast<IGenericTeamAgentInterface>(PawnToCheck->GetController());

	if (OtherTeamAgent && OtherTeamAgent->GetGenericTeamId() < GetGenericTeamId())
		return ETeamAttitude::Hostile;
	return ETeamAttitude::Friendly;
}

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();

	if (UCrowdFollowingComponent* CrowdFollowingComponent = Cast<UCrowdFollowingComponent>(GetPathFollowingComponent()))
	{
		CrowdFollowingComponent->SetCrowdSimulationState(bEnableDetourCrowdAvoidance
			                                                 ? ECrowdSimulationState::Enabled
			                                                 : ECrowdSimulationState::Disabled);
		switch (DetourCrowdAvoidanceQuality)
		{
		case 1:
			CrowdFollowingComponent->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::Low);
			break;
		case 2:
			CrowdFollowingComponent->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::Medium);
			break;
		case 3:
			CrowdFollowingComponent->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::Good);
			break;
		case 4:
			CrowdFollowingComponent->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::High);
			break;
		default: break;
		}

		CrowdFollowingComponent->SetAvoidanceGroup(1);
		CrowdFollowingComponent->SetGroupsToAvoid(1);
		CrowdFollowingComponent->SetCrowdCollisionQueryRange(CrowdCollisionQueryRange);
	}
}

void AEnemyAIController::OnEnemyPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if (UBlackboardComponent* BlackboardComponent = GetBlackboardComponent())
	{
		if (!BlackboardComponent->GetValueAsObject(FName("TargetActor")))
		{
			if (Stimulus.WasSuccessfullySensed() && Actor)
				BlackboardComponent->SetValueAsObject(FName("TargetActor"), Actor);
		}
	}
}
