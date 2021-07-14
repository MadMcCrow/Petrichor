// Copyright © Noé Perard-Gayot 2021.


#include "Player/PTRPlayerState.h"
#include "Items/PTRInventoryComponent.h"
#include "GameplayAbilitySystem/PTRAbilitySystemComponent.h"

FName APTRPlayerState::InventoryComponentName	= TEXT("InventoryComponent");
FName APTRPlayerState::GASComponentName			= TEXT("AbilitySystemComponent");

APTRPlayerState::APTRPlayerState(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PlayerInventory			= ObjectInitializer.CreateDefaultSubobject<UPTRInventoryComponent>(this, InventoryComponentName, true);
	AbilitySystemComponent	= ObjectInitializer.CreateDefaultSubobject<UPTRAbilitySystemComponent>(this, GASComponentName);
	AbilitySystemComponent->SetIsReplicated(true);
}

UAbilitySystemComponent* APTRPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}