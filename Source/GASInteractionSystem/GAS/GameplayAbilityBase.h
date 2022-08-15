// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GASInteractionSystem/GASInteractionSystem.h"
#include "Abilities/GameplayAbility.h"
#include "GameplayAbilityBase.generated.h"


UCLASS()
class GASINTERACTIONSYSTEM_API UGameplayAbilityBase : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	UGameplayAbilityBase();

	virtual void OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;

	// Abilities with this set will automatically activate when input is pressed.
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "GAS")
	EAbilityInputID AbilityInputID;

protected:
	// Tells an ability to activate immediately when its granted. Used for passive abilities and abilites forced on others.
	// If true, NetSecurityPolicy and NetExecutionPolicy need to be set to ServerOnly.
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "GAS")
	bool bActivateWhenGranted;
};
