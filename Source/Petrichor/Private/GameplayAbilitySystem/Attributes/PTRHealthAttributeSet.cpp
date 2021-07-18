// Copyright © Noé Perard-Gayot 2021.

#include "GameplayAbilitySystem/Attributes/PTRHealthAttributeSet.h"
#include "Net/UnrealNetwork.h"

UPTRHealthAttributeSet::UPTRHealthAttributeSet(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void UPTRHealthAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPTRHealthAttributeSet, Health, OldHealth);
}

void UPTRHealthAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPTRHealthAttributeSet, MaxHealth, OldMaxHealth);
}

void UPTRHealthAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UPTRHealthAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPTRHealthAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
}