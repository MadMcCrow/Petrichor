// Copyright © Noé Perard-Gayot 2021.

#include "UI/PTRHUDWidget.h"
#include "Characters/PTRCharacter.h"
#include "Player/PTRPlayerState.h"

class APTRCharacter* UPTRHUDWidget::GetPTRCharacter() const
{
	if (GetOwningPlayer())
	{
		return Cast<APTRCharacter>(GetOwningPlayer()->GetPawn());
	}
	return nullptr;
}

APTRPlayerState* UPTRHUDWidget::GetPTRPlayerState() const
{
	if (GetOwningPlayer())
	{
		return GetOwningPlayer()->GetPlayerState<APTRPlayerState>();
	}
	return nullptr;
}

void UPTRHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();
}