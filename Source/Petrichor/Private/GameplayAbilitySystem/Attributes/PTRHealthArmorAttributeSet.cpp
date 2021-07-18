// Copyright © Noé Perard-Gayot 2021.

#include "GameplayAbilitySystem/Attributes/PTRHealthArmorAttributeSet.h"
#include "Net/UnrealNetwork.h"

UPTRHealthArmorAttributeSet::UPTRHealthArmorAttributeSet(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void UPTRHealthArmorAttributeSet::OnRep_Armor(const FGameplayAttributeData& OldArmor)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPTRHealthArmorAttributeSet, Armor, OldArmor);
}

void UPTRHealthArmorAttributeSet::OnRep_MaxArmor(const FGameplayAttributeData& OldMaxArmor)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPTRHealthArmorAttributeSet, MaxArmor, OldMaxArmor);
}

void UPTRHealthArmorAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UPTRHealthArmorAttributeSet, Armor, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPTRHealthArmorAttributeSet, MaxArmor, COND_None, REPNOTIFY_Always);
}