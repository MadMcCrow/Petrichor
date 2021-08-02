// Copyright © Noé Perard-Gayot 2021. Licenced under LGPL-3.0-or-later
// You should have received a copy of the GNU Lesser General Public License
// along with Petrichor. If not, see <https://www.gnu.org/licenses/>.

#pragma once

#include "CoreMinimal.h"
#include "PTRInventoryInterface.generated.h"

// forward declaration
class UPTRInventoryComponent;

/**
 *	Simple Interface to easily get inventory on a class
 */
UINTERFACE(MinimalAPI, Blueprintable, Category="Petrichor|Attributes")
class UPTRInventoryInterface : public UInterface
{
	GENERATED_BODY()
};

class IPTRInventoryInterface
{
	GENERATED_BODY()

public:
	/** return Inventory component */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category  = "Inventory")
	UPTRInventoryComponent* GetInventoryComponent() const;
	virtual UPTRInventoryComponent* GetInventoryComponent_Implementation() const PURE_VIRTUAL(,return nullptr;)
};
