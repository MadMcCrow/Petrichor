// Copyright © Noé Perard-Gayot 2021. Licenced under LGPL-3.0-or-later
// You should have received a copy of the GNU Lesser General Public License
// along with Petrichor. If not, see <https://www.gnu.org/licenses/>.

#include "Attributes/PTRAttributeComponent.h"
#include "Items/PTRInventoryInterface.h"

UPTRAttributeComponent::UPTRAttributeComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void UPTRAttributeComponent::InitAttributes(const TArray<FPTRAttributeDefinition> InAttributes)
{
	// explicit conversion
	Attributes = TSet<FPTRAttributeDefinition>(InAttributes);
}

FPTRAttribute UPTRAttributeComponent::GetAttribute(const FPTRSoftItemPath& InItem) const
{
	return FPTRAttribute(GetAttributeCount(InItem), GetAttributeBaseValue(InItem));
}

int32 UPTRAttributeComponent::GetAttributeBaseValue(const FPTRSoftItemPath& InItem) const
{
	if (const FPTRAttributeDefinition* Attribute = Attributes.Find(FPTRAttributeDefinition(InItem)))
	{
		return Attribute->BaseValue;
	}
	return 0;
}

int32 UPTRAttributeComponent::GetAttributeCount(const FPTRSoftItemPath& InItem) const
{
	if (GetInventoryComponent())
	{
		return GetInventoryComponent()->ItemCount(InItem);
	}
	return 0;
}

UPTRInventoryComponent* UPTRAttributeComponent::GetInventoryComponent() const
{
	return IPTRInventoryInterface::Execute_GetInventoryComponent(GetOwner());
}
