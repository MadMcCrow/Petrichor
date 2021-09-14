// Copyright © Noé Perard-Gayot 2021. Licenced under LGPL-3.0-or-later
// You should have received a copy of the GNU Lesser General Public License
// along with Petrichor. If not, see <https://www.gnu.org/licenses/>.


#include "Player/PTRPlayerState.h"
#include "Engine/AssetManager.h"
#include "Items/PTRInventoryComponent.h"
#include "Attributes/PTRAttributeComponent.h"
#include "Items/PTRItemTableRow.h"

FName APTRPlayerState::InventoryComponentName = TEXT("InventoryComponent");
FName APTRPlayerState::AttributeComponentName = TEXT("AttributeComponent");


APTRPlayerState::APTRPlayerState(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PlayerInventory = ObjectInitializer.CreateDefaultSubobject<UPTRInventoryComponent>(
		this, InventoryComponentName, true);
	PlayerAttributes = ObjectInitializer.CreateDefaultSubobject<UPTRAttributeComponent>(
		this, AttributeComponentName, true);
}

void APTRPlayerState::BeginPlay()
{
	Super::BeginPlay();
	if (GetLocalRole() == ROLE_Authority)
	{
		if (PlayerInventory)
		{
			if (const UDataTable* ItemDataTable = Cast<UDataTable>(StartingItem.TryLoad()))
			{
				UAssetManager* Manager = UAssetManager::GetIfValid();

				if (!Manager)
				{
					return;
				}

				TMap<FPTRSoftItemPath, int32> InitItems;
				ItemDataTable->ForeachRow<FPTRItemTableRow>(
					TEXT("APTRPlayerState : Getting Starting items"),
					[&Manager, &InitItems](const FName &RowName, const FPTRItemTableRow& Row)
					{
						const auto AssetPath = Manager->GetPrimaryAssetPath(Row.AssetId);
						if (!AssetPath.IsNull())
						{
							InitItems.Add(FPTRSoftItemPath(AssetPath), Row.Count);
						}
					});
				// init the inventory
				PlayerInventory->InitInventory(InitItems);
			}
		}
		if (PlayerAttributes)
		{
			if (const UDataTable* AttributesDataTable = Cast<UDataTable>(AttributesDefinition.TryLoad()))
			{
				TArray<FPTRAttributeDefinition> AttributesArray;
				AttributesDataTable->ForeachRow<FPTRAttributeDefinition>(
					TEXT("APTRPlayerState : Getting Attributes"),
					[&AttributesArray](const FName& Key, const FPTRAttributeDefinition& Value)
					{
						AttributesArray.AddUnique(Value);
					});
				PlayerAttributes->InitAttributes(AttributesArray);
			}
		}
	}
}
