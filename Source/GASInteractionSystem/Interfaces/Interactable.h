// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interactable.generated.h"


// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable)
class UInteractable : public UInterface
{
	GENERATED_BODY()
};

class GASINTERACTIONSYSTEM_API IInteractable
{
	GENERATED_BODY()

public:
	// Returns true if the owner of the passed ASC can interact with this interactable.
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interactable")
	bool CanInteractWith(class UAbilitySystemComponent* InteractorASC) const;

	// Called on the client and server
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interactable")
	void Interact(class UAbilitySystemComponent* InteractorASC);

	// Called when the interactable either receives or loses focus
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, BlueprintCosmetic, Category = "Interactable|Client Only")
	void OnFocusChanged(bool bIsFocus, class UAbilitySystemComponent* InteractorASC);

	// Called if the interaction failed (ie, Interactable on cooldown, ASC doesn't meet requirements, etc)
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, BlueprintCosmetic, Category = "Interactable|Client Only")
	void InteractionFailed(class UAbilitySystemComponent* InteractorASC);
};