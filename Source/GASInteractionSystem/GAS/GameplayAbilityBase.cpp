// Fill out your copyright notice in the Description page of Project Settings.

#include "GASInteractionSystem/GAS/GameplayAbilityBase.h"

#include "AbilitySystemComponent.h"


UGameplayAbilityBase::UGameplayAbilityBase()
	: AbilityInputID(EAbilityInputID::None), bActivateWhenGranted(false)
{
	// Default to Instanced Per Actor
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UGameplayAbilityBase::OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnAvatarSet(ActorInfo, Spec);

	// If this ability is activated automatically, server needs to activate it
	if (bActivateWhenGranted && ActorInfo->IsNetAuthority())
	{
		// Abillity NEEDS these settings or weird things will happen; ensure they are set correctly
		ensure(NetSecurityPolicy == EGameplayAbilityNetSecurityPolicy::ServerOnly && NetExecutionPolicy == EGameplayAbilityNetExecutionPolicy::ServerOnly);

		ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle, true);
	}
}