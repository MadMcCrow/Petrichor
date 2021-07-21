// Copyright © Noé Perard-Gayot 2021.

#pragma once

#include "Attributes/PTRAttributeInterface.h"
#include "Items/PTRInventoryComponent.h"

UPTRInventoryComponent* IPTRAttributeInterface::GetInventoryComponent_Implementation() const
{
	if (const auto ThisActor = Cast<AActor>(this))
	{
		if (const auto Comp = ThisActor->GetComponentByClass(UPTRInventoryComponent::StaticClass()))
		{
			return Cast<UPTRInventoryComponent>(Comp);
		}
	}
	return nullptr;
}