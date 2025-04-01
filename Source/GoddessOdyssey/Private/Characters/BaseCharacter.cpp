#include "Characters/BaseCharacter.h"

#include "DebugHelper.h"
#include "AbilitySystems/BaseAbilitySystemComponent.h"
#include "AbilitySystems/BaseAttributeSet.h"
#include "MotionWarpingComponent.h"
#include "GameModes/GoddessSurvivalGameMode.h"
#include "GoddessTypes/GoddessEnumTypes.h"

ABaseCharacter::ABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;
	// 将 bReceivesDecals 设置为 false 表示禁用该网格组件接收贴花的功能
	GetMesh()->bReceivesDecals = false;

	BaseAbilitySystemComponent = CreateDefaultSubobject<UBaseAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	BaseAttributeSet = CreateDefaultSubobject<UBaseAttributeSet>(TEXT("AttributeSet"));
	MotionWarpingComponent = CreateDefaultSubobject<UMotionWarpingComponent>(TEXT("MotionWarpingComponent"));
}

UAbilitySystemComponent* ABaseCharacter::GetAbilitySystemComponent() const
{
	return GetBaseAbilitySystemComponent();
}

UBaseCombatComponent* ABaseCharacter::GetCombatComponentByInterface() const
{
	return nullptr;
}

UBaseUIComponent* ABaseCharacter::GetUIComponentByInterface() const
{
	return nullptr;
}

void ABaseCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (BaseAbilitySystemComponent)
	{
		BaseAbilitySystemComponent->InitAbilityActorInfo(this, this);

		ensureMsgf(!CharacterStartUpData.IsNull(), TEXT("Forgot to assign start up data to %s"), *GetName());
	}
}

int32 ABaseCharacter::GetCurrentAbilityApplyLevel() const
{
	int32 AbilityApplyLevel = 1;

	if (AGoddessGameMode* BaseGameMode = GetWorld()->GetAuthGameMode<AGoddessGameMode>())
	{
		switch (BaseGameMode->GetCurrentGameDifficulty())
		{
		case EGoddessGameDifficulty::Easy:
			AbilityApplyLevel = 1;
			Debug::Print(TEXT("Current Difficulty: Easy"));
			break;
		case EGoddessGameDifficulty::Normal:
			AbilityApplyLevel = 2;
			Debug::Print(TEXT("Current Difficulty: Normal"));
			break;
		case EGoddessGameDifficulty::Hard:
			AbilityApplyLevel = 3;
			Debug::Print(TEXT("Current Difficulty: Hard"));
			break;
		case EGoddessGameDifficulty::VeryHard:
			AbilityApplyLevel = 4;
			Debug::Print(TEXT("Current Difficulty: VeryHard"));
			break;
		default:
			break;
		}
	}

	return AbilityApplyLevel;
}
