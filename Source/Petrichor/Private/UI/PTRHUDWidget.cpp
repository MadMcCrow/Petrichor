// Copyright © Noé Perard-Gayot 2021.

#include "UI/PTRHUDWidget.h"

#include "Characters/PTRCharacter.h"
#include "GameplayAbilitySystem/PTRAbilitySystemComponent.h"


class APTRCharacter* UPTRHUDWidget::GetPTRCharacter() const
{
	return Cast<APTRCharacter>(GetOwningPlayer()->GetPawn());
}

class UPTRAbilitySystemComponent* UPTRHUDWidget::GetPTRGameplayAbilitySystem() const
{
	return Cast<UPTRAbilitySystemComponent>(GetPTRCharacter()->GetAbilitySystemComponent());
}

void UPTRHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();
}