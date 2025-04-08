// Fill out your copyright notice in the Description page of Project Settings.


#include "GoddessFunctionLibrary.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "DebugHelper.h"
#include "GameplayTagContainer.h"
#include "GenericTeamAgentInterface.h"
#include "GoddessGameplayTags.h"
#include "AbilitySystems/BaseAbilitySystemComponent.h"
#include "GoddessTypes/GoddessCountdownAction.h"
#include "Interfaces/CombatComponentInterface.h"
#include "Kismet/KismetMathLibrary.h"
#include "GoddessGameInstance.h"
#include "Components/Inventory/GoddessInventoryComponent.h"
#include "GoddessTypes/GoddessStructTypes.h"
#include "Item/PickUps/InventoryItemBase.h"
#include "Kismet/GameplayStatics.h"
#include "SaveGame/GoddessSaveGame.h"

UBaseAbilitySystemComponent* UGoddessFunctionLibrary::NativeGetASCFromActor(AActor* InActor)
{
	check(InActor);

	return Cast<UBaseAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(InActor));
}

void UGoddessFunctionLibrary::AddGameplayTagToActorIfNone(AActor* InActor, FGameplayTag TagToAdd)
{
	UBaseAbilitySystemComponent* ASC = NativeGetASCFromActor(InActor);

	if (!ASC->HasMatchingGameplayTag(TagToAdd))
		ASC->AddLooseGameplayTag(TagToAdd);
}

void UGoddessFunctionLibrary::RemoveGameplayTagFromActorIfFound(AActor* InActor, FGameplayTag TagToRemove)
{
	UBaseAbilitySystemComponent* ASC = NativeGetASCFromActor(InActor);

	if (ASC->HasMatchingGameplayTag(TagToRemove))
		ASC->RemoveLooseGameplayTag(TagToRemove);
}

bool UGoddessFunctionLibrary::NativeDoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck)
{
	UBaseAbilitySystemComponent* ASC = NativeGetASCFromActor(InActor);

	return ASC->HasMatchingGameplayTag(TagToCheck);
}

void UGoddessFunctionLibrary::BP_DoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck,
                                                  EGoddessConfirmType& OutConfirmType)
{
	OutConfirmType = NativeDoesActorHaveTag(InActor, TagToCheck) ? EGoddessConfirmType::Yes : EGoddessConfirmType::No;
}

UBaseCombatComponent* UGoddessFunctionLibrary::NativeGetCombatComponentFromActor(AActor* InActor)
{
	check(InActor);

	if (ICombatComponentInterface* CombatComponentInterface = Cast<ICombatComponentInterface>(InActor))
		return CombatComponentInterface->GetCombatComponentByInterface();
	return nullptr;
}

UBaseCombatComponent* UGoddessFunctionLibrary::BP_GetCombatComponentFromActor(
	AActor* InActor, EGoddessValidType& OutValidType)
{
	UBaseCombatComponent* CombatComponent = NativeGetCombatComponentFromActor(InActor);

	OutValidType = CombatComponent ? EGoddessValidType::Valid : EGoddessValidType::Invalid;

	return CombatComponent;
}

bool UGoddessFunctionLibrary::IsTargetPawnHostile(APawn* QueryPawn, APawn* TargetPawn)
{
	check(QueryPawn && TargetPawn);

	IGenericTeamAgentInterface* QueryTeamAgent = Cast<IGenericTeamAgentInterface>(QueryPawn->GetController());
	IGenericTeamAgentInterface* TargetTeamAgent = Cast<IGenericTeamAgentInterface>(TargetPawn->GetController());

	if (QueryTeamAgent && TargetTeamAgent)
		return QueryTeamAgent->GetGenericTeamId() != TargetTeamAgent->GetGenericTeamId();

	return false;
}

float UGoddessFunctionLibrary::GetScalableFloatValueAtLevel(const FScalableFloat& InScalableFloat, float InLevel)
{
	return InScalableFloat.GetValueAtLevel(InLevel);
}

FGameplayTag UGoddessFunctionLibrary::ComputeHitReactDirectionTag(AActor* InAttacker, AActor* InVictim,
                                                                  float& OutAngleDiff)
{
	check(InAttacker && InVictim);

	const FVector VictimForward = InVictim->GetActorForwardVector();
	const FVector VictimToAttackerNormalized =
		(InAttacker->GetActorLocation() - InVictim->GetActorLocation()).GetSafeNormal();

	const float DotResult = FVector::DotProduct(VictimForward, VictimToAttackerNormalized);
	OutAngleDiff = UKismetMathLibrary::DegAcos(DotResult);

	const FVector CrossResult = FVector::CrossProduct(VictimForward, VictimToAttackerNormalized);
	if (CrossResult.Z < 0)
		OutAngleDiff *= -1;

	if (OutAngleDiff >= -45.f && OutAngleDiff < 45.f)
		return GoddessGameplayTags::Shared_Status_HitReact_Front;
	if (OutAngleDiff >= -135.f && OutAngleDiff < -45.f)
		return GoddessGameplayTags::Shared_Status_HitReact_Left;
	if (OutAngleDiff >= 45.f && OutAngleDiff < 135.f)
		return GoddessGameplayTags::Shared_Status_HitReact_Right;
	if (OutAngleDiff < -135.f || OutAngleDiff > 135.f)
		return GoddessGameplayTags::Shared_Status_HitReact_Back;
	return GoddessGameplayTags::Shared_Status_HitReact_Front;
}

bool UGoddessFunctionLibrary::IsValidBlock(AActor* InAttacker, AActor* InDefender)
{
	check(InAttacker && InDefender);

	const float DotResult =
		FVector::DotProduct(InAttacker->GetActorForwardVector(), InDefender->GetActorForwardVector());
	// const FString result = FString::Printf(TEXT("Dot result: %f , %s"), DotResult,
	//                                        DotResult < -0.3f ? TEXT("Valid") : TEXT("Invalid"));
	//
	// Debug::Print(result, DotResult < -0.3f ? FColor::Green : FColor::Red);

	return DotResult < -0.3f;
}

bool UGoddessFunctionLibrary::ApplyGameplayEffectSpecHandleToTargetActor(AActor* InInstigator, AActor* InTargetActor,
                                                                         const FGameplayEffectSpecHandle& InSpecHandle)
{
	UBaseAbilitySystemComponent* SourceASC = NativeGetASCFromActor(InInstigator);
	UBaseAbilitySystemComponent* TargetASC = NativeGetASCFromActor(InTargetActor);

	FActiveGameplayEffectHandle ActiveGameplayEffectHandle =
		SourceASC->ApplyGameplayEffectSpecToTarget(*InSpecHandle.Data, TargetASC);

	return ActiveGameplayEffectHandle.WasSuccessfullyApplied();
}

void UGoddessFunctionLibrary::CountDown(
	const UObject* WorldContextObject,
	float TotalTime,
	float UpdateInterval,
	float& OutRemainingTime,
	EGoddesssCountDownActionInput CountDownInput,
	UPARAM(DisplayName = "Output") EGoddesssCountDownActionOutput& CountDownOutput,
	FLatentActionInfo LatentInfo)
{
	UWorld* World = nullptr;

	if (GEngine)
		World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	if (!World) return;

	FLatentActionManager& LatentActionManager = World->GetLatentActionManager();

	FGoddessCountDownAction* FoundAction =
		LatentActionManager.FindExistingAction<FGoddessCountDownAction>(LatentInfo.CallbackTarget, LatentInfo.UUID);

	if (CountDownInput == EGoddesssCountDownActionInput::Start)
	{
		if (!FoundAction)
		{
			LatentActionManager.AddNewAction(
				LatentInfo.CallbackTarget,
				LatentInfo.UUID,
				new FGoddessCountDownAction(TotalTime, UpdateInterval, OutRemainingTime, CountDownOutput, LatentInfo)
			);
		}
	}

	if (CountDownInput == EGoddesssCountDownActionInput::Cancel)
	{
		if (FoundAction)
			FoundAction->CancelAction();
	}
}

UGoddessGameInstance* UGoddessFunctionLibrary::GetGoddessGameInstance(const UObject* WorldContextObject)
{
	if (GEngine)
	{
		if (UWorld* World = GEngine->
			GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
			return World->GetGameInstance<UGoddessGameInstance>();
	}
	return nullptr;
}

void UGoddessFunctionLibrary::ToggleInputMode(const UObject* WorldContextObject, EGoddessInputMode InInputMode)
{
	APlayerController* PlayerController = nullptr;
	if (GEngine)
	{
		if (UWorld* World = GEngine->
			GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
			PlayerController = World->GetFirstPlayerController();
	}
	if (!PlayerController) return;

	FInputModeGameOnly GameOnlyInputMode;
	FInputModeUIOnly UIOnlyInputMode;
	UIOnlyInputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);

	switch (InInputMode)
	{
	case EGoddessInputMode::GameOnly:
		PlayerController->SetInputMode(GameOnlyInputMode);
		PlayerController->bShowMouseCursor = false;
		break;
	case EGoddessInputMode::UIOnly:
		PlayerController->SetInputMode(UIOnlyInputMode);
		PlayerController->bShowMouseCursor = true;
		break;
	}
}

void UGoddessFunctionLibrary::SaveCurrentGameDifficulty(EGoddessGameDifficulty InDifficultyToSave)
{
	USaveGame* SaveGameObject = UGameplayStatics::CreateSaveGameObject(UGoddessSaveGame::StaticClass());

	if (UGoddessSaveGame* GoddessSaveGameObject = Cast<UGoddessSaveGame>(SaveGameObject))
	{
		GoddessSaveGameObject->SavedCurrentGameDifficulty = InDifficultyToSave;

		const bool bWasSaved = UGameplayStatics::SaveGameToSlot(
			GoddessSaveGameObject,
			GoddessGameplayTags::GameData_SaveGame_Slot_1.GetTag().ToString(),
			0
		);

		Debug::Print(bWasSaved ? TEXT("Difficulty Was Saved") : TEXT("Difficulty Not Saved"));
	}
}

bool UGoddessFunctionLibrary::TryLoadSavedGameDifficulty(EGoddessGameDifficulty& OutSavedDifficulty)
{
	if (UGameplayStatics::DoesSaveGameExist(GoddessGameplayTags::GameData_SaveGame_Slot_1.GetTag().ToString(), 0))
	{
		USaveGame* SavedGameObject = UGameplayStatics::LoadGameFromSlot(
			GoddessGameplayTags::GameData_SaveGame_Slot_1.GetTag().ToString(), 0);

		if (UGoddessSaveGame* GoddessSaveGameObject = Cast<UGoddessSaveGame>(SavedGameObject))
		{
			OutSavedDifficulty = GoddessSaveGameObject->SavedCurrentGameDifficulty;

			Debug::Print(TEXT("Loading Successful"), FColor::Green);

			return true;
		}
	}
	return false;
}

FString UGoddessFunctionLibrary::ConvFloatToString(float Number)
{
	int32 IntPart = FMath::FloorToInt(Number);

	if (IntPart < 1000)
		return FString::FromInt(IntPart);

	int32 ThousandPart = IntPart / 1000;
	int32 LowerOrderPart = IntPart % 1000;

	FString NumberStr = FString::Printf(TEXT("%d,%03d"), ThousandPart, LowerOrderPart);
	return NumberStr;
}

void UGoddessFunctionLibrary::AddItemToInventory(UGoddessInventoryComponent* InInventoryComp,
                                                 AInventoryItemBase* InventoryItem)
{
	FGoddessInventoryItemData NewInventoryItemData = InInventoryComp->GetSavedInventoryItemData();
	UDataTable* AllInventoryItemsDataTable = InInventoryComp->GetAllInventoryItemsDataTable();
	if (AllInventoryItemsDataTable)
	{
		InventoryItem->AddToInventory(AllInventoryItemsDataTable, NewInventoryItemData);
		InInventoryComp->SetSavedInventoryItemData(NewInventoryItemData);
		// GetGoddessInventoryComponentFromActorInfo()->PrintSavedInventoryItemData();
	}
	else
		Debug::Print(TEXT("AllInventoryItemsDataTable is nullptr"));
}
