// Copyright © Noé Perard-Gayot 2021.


#include "Player/PTRPlayerState.h"
#include "Items/PTRInventoryComponent.h"
#include "GameplayAbilitySystem/PTRAbilitySystemComponent.h"
#include "GameplayAbilitySystem/Attributes/PTRCharacterAttributeSet.h"

FName APTRPlayerState::InventoryComponentName	= TEXT("InventoryComponent");
FName APTRPlayerState::GASComponentName			= TEXT("AbilitySystemComponent");

APTRPlayerState::APTRPlayerState(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PlayerInventory			= ObjectInitializer.CreateDefaultSubobject<UPTRInventoryComponent>(this, InventoryComponentName, true);
	AbilitySystemComponent	= ObjectInitializer.CreateDefaultSubobject<UPTRAbilitySystemComponent>(this, GASComponentName);
	AbilitySystemComponent->SetIsReplicated(true);

	// Create the attribute set, this replicates by default
	// Adding it as a subobject of the owning actor of an AbilitySystemComponent
	// automatically registers the AttributeSet with the AbilitySystemComponent
	CharacterAttributeSet = CreateDefaultSubobject<UPTRCharacterAttributeSet>(TEXT("CharacterAttributeSet"));
}

UAbilitySystemComponent* APTRPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}