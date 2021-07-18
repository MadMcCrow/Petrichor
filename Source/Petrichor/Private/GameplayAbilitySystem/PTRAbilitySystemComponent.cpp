// Copyright © Noé Perard-Gayot 2021.

#include "GameplayAbilitySystem/PTRAbilitySystemComponent.h"

UPTRAbilitySystemComponent::UPTRAbilitySystemComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void UPTRAbilitySystemComponent::BeginPlay()
{
	Super::BeginPlay();

	for (const TSoftClassPtr<UGameplayEffect>& EffectItr :DefaultEffects)
	{
		TSubclassOf<UGameplayEffect> EffectClass = EffectItr.LoadSynchronous();
		if (EffectClass)
		{
			if (UGameplayEffect* GameplayEffect = Cast<UGameplayEffect>(EffectClass->GetDefaultObject()))
			{
				ApplyGameplayEffectToSelf(GameplayEffect, 0.f, MakeEffectContext(), GetPredictionKeyForNewAction());
			}
		}
	}
}