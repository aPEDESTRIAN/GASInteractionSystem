// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "GASInteractionSystem/GAS/CharacterAttributeSet.h"
#include "GASInteractionSystemCharacter.generated.h"


UCLASS(config=Game)
class AGASInteractionSystemCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AGASInteractionSystemCharacter(const FObjectInitializer& ObjectInitializer);

	// Called when this Pawn is possessed. Only called on the server.
	virtual void PossessedBy(AController* NewController) override;

	// Called when the player state is replicated. Only called on clients.
	virtual void OnRep_PlayerState() override;


// =================================================================
// ============================[ INPUT ]============================
// =================================================================
#pragma region INPUT

public:
	// Base turn rate, in deg/sec. Other scaling may affect final turn rate.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input)
	float TurnRateGamepad;

protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float Value);
	void MoveRight(float Value);

	void TurnAtRate(float Rate);
	void LookUpAtRate(float Rate);

	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

#pragma endregion


// =================================================================
// ============================[ CAMERA ]===========================
// =================================================================
#pragma region CAMERA

public:
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

private:
	// Camera boom positioning the camera behind the character
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	// Follow camera
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

#pragma endregion


// =================================================================
// ===================[ GAMEPLAY_ABILITY_SYSTEM ]===================
// =================================================================
#pragma region GAMEPLAY_ABILITY_SYSTEM

public:
	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystemComponent; }

	UFUNCTION(BlueprintPure, Category = "GAS|Attributes")
	float GetSpeed() const { return IsValid(AttributeSet) ? AttributeSet->GetSpeed() : 0.0f; }

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS")
	class UAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY(BlueprintReadOnly, Category = "GAS")
	class UCharacterAttributeSet* AttributeSet;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GAS")
	TSubclassOf<class UGameplayEffect> DefaultAttributesEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GAS")
	TArray<TSubclassOf<class UGameplayAbilityBase>> DefaultAbilities;

private:
	void ClientSetupGAS();
	void ServerSetupGAS();

	void InitializeAttributes() const;
	void GiveDefaultAbilities();
	void BindAbilitiesToInput() const;

#pragma endregion


// =================================================================
// =========================[ INTERACTION ]=========================
// =================================================================
#pragma region INTERACTION
public:
	UFUNCTION(BlueprintPure, Category = "Interaction")
	AActor* GetClosestInteractable() const;

	// If bFocus is true, this actor will scan for interactables
	// Should ONLY be set to true on local client
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void SetFocusInteractables(bool bFocus);

private:
	UPROPERTY()
	AActor* CurrentFocus = nullptr;

	FTimerHandle InteractableCheckTimer;

	UFUNCTION(BlueprintCosmetic)
	void FocusClosestInteractable();

#pragma endregion

};