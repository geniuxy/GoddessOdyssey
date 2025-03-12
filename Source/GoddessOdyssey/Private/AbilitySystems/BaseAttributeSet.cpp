// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystems/BaseAttributeSet.h"
#include "GameplayEffectExtension.h"

#include "DebugHelper.h"
#include "GoddessFunctionLibrary.h"
#include "GoddessGameplayTags.h"
#include "Components/UI/BaseUIComponent.h"
#include "Components/UI/GoddessUIComponent.h"
#include "Interfaces/UIComponentInterface.h"

UBaseAttributeSet::UBaseAttributeSet()
{
	InitCurrentHealth(1.f);
	InitMaxHealth(1.f);
	InitCurrentRage(1.f);
	InitMaxRage(1.f);
	InitAttackPower(1.f);
	InitDefensePower(1.f);
}

void UBaseAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	if (!CachedBaseUIInterface.IsValid())
		CachedBaseUIInterface = TWeakInterfacePtr<IUIComponentInterface>(Data.Target.GetAvatarActor());
	checkf(CachedBaseUIInterface.IsValid(),
	       TEXT("%s didn't implement IPawnUIInterface"), *Data.Target.GetAvatarActor()->GetActorNameOrLabel());
	UBaseUIComponent* BaseUIComponent = CachedBaseUIInterface->GetUIComponentByInterface();
	checkf(BaseUIComponent,
	       TEXT("Couldn't extract a PawnUIComponent from %s"), *Data.Target.GetAvatarActor()->GetActorNameOrLabel());

	// GameplayEffectExtension include 之后，才能有Data.EvaluatedData
	if (Data.EvaluatedData.Attribute == GetCurrentHealthAttribute())
	{
		const float NewCurrentHealth = FMath::Clamp(GetCurrentHealth(), 0.f, GetMaxHealth());

		SetCurrentHealth(NewCurrentHealth);

		BaseUIComponent->OnCurrentHealthChanged.Broadcast(GetCurrentHealth() / GetMaxHealth());
	}

	if (Data.EvaluatedData.Attribute == GetCurrentRageAttribute())
	{
		const float NewCurrentRage = FMath::Clamp(GetCurrentRage(), 0.f, GetMaxRage());

		SetCurrentHealth(NewCurrentRage);

		if (UGoddessUIComponent* GoddessUIComponent = CachedBaseUIInterface->GetGoddessUIComponentByInterface())
			GoddessUIComponent->OnCurrentRageChanged.Broadcast(GetCurrentRage() / GetMaxRage());
	}

	if (Data.EvaluatedData.Attribute == GetDamageTakenAttribute())
	{
		const float OldHealth = GetCurrentHealth();
		const float Damage = GetDamageTaken();

		const float NewCurrentHealth = FMath::Clamp(OldHealth - Damage, 0.f, GetMaxHealth());

		SetCurrentHealth(NewCurrentHealth);

		const FString DebugString = FString::Printf(
			TEXT("Old Health: %f, Damage Done: %f, NewCurrentHealth: %f"),
			OldHealth,
			Damage,
			NewCurrentHealth
		);

		Debug::Print(DebugString, FColor::Green);

		// Notify the UI
		BaseUIComponent->OnCurrentHealthChanged.Broadcast(GetCurrentHealth() / GetMaxHealth());

		// Handle character death
		if (GetCurrentHealth() == 0.f)
		{
			UGoddessFunctionLibrary::AddGameplayTagToActorIfNone(
				Data.Target.GetAvatarActor(), GoddessGameplayTags::Shared_Status_Death);
		}
	}
}
