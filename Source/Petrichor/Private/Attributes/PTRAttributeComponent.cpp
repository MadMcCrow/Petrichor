// Copyright © Noé Perard-Gayot 2021.

#include "Attributes/PTRAttributeComponent.h"

#include "GameFramework/Actor.h"

#include "Attributes/PTRAttributeInterface.h"
#include "Attributes/PTRAttributeSubsystem.h"
#include "Items/PTRInventoryComponent.h"


UPTRAttributeComponent::UPTRAttributeComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void UPTRAttributeComponent::OnRegister()
{
	Super::OnRegister();

	// Update Default Attributes with DTB
	if (!AttributesDatatable.IsNull())
	{
		if (auto DTB = Cast<UDataTable>(AttributesDatatable.TryLoad()))
		{
			TArray<FPTRAttributeStats*> Attributes;
			DTB->GetAllRows<FPTRAttributeStats>("UPTRAttributeComponent::OnRegister : ReadAttributes from DTB", Attributes);
			for (auto AttItr : Attributes)
			{
				if (AttItr)
				{
					DefaultAttributes.AddUnique(*AttItr);
				}
			}
		}
	}
	// Done
}

UPTRInventoryComponent* UPTRAttributeComponent::GetInventoryComponent() const
{
	if (GetOwner()->Implements<UPTRAttributeInterface>())
		return IPTRAttributeInterface::Execute_GetInventoryComponent(GetOwner());
	return nullptr;
}

int32 UPTRAttributeComponent::GetAttributeByName(FName InternalName) const
{
	if (const auto AttributeSS = UPTRAttributeSubsystem::GetAttributeSubsystem())
	{
		if (const auto Inv = GetInventoryComponent())
		{
			return Inv->ItemCount(AttributeSS->GetAttribute(InternalName));
		}
	}
	return 0;
}

int32 UPTRAttributeComponent::GetAttributeByClass(UClass* AttributeClass) const
{
	if (const auto AttributeSS = UPTRAttributeSubsystem::GetAttributeSubsystem())
	{
		if (const auto Inv = GetInventoryComponent())
		{
			return Inv->ItemCount(AttributeSS->GetAttribute(AttributeClass));
		}
	}
	return 0;
}

int32 UPTRAttributeComponent::GetAttributeBaseByName(FName InternalName) const
{
	if (const auto AttributeSS = UPTRAttributeSubsystem::GetAttributeSubsystem())
	{
		const auto SoftPath = AttributeSS->GetAttribute(InternalName);
		if (auto Found = DefaultAttributes.FindByPredicate([&SoftPath](const FPTRAttributeStats& Itr) {return Itr.Attribute == SoftPath;}))
		{
			return Found->BaseValue;
		}
	}
	return 0;
}

int32 UPTRAttributeComponent::GetAttributeBaseByClass(UClass* AttributeClass) const
{
	if (const auto AttributeSS = UPTRAttributeSubsystem::GetAttributeSubsystem())
	{
		const auto SoftPath = AttributeSS->GetAttribute(AttributeClass);
		if (auto Found = DefaultAttributes.FindByPredicate([&SoftPath](const FPTRAttributeStats& Itr) {return Itr.Attribute == SoftPath;}))
		{
			return Found->BaseValue;
		}
	}
	return 0;
}