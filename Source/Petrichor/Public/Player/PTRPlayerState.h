// Copyright © Noé Perard-Gayot 2021. Licenced under LGPL-3.0-or-later
// You should have received a copy of the GNU Lesser General Public License
// along with Petrichor. If not, see <https://www.gnu.org/licenses/>.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "Items/PTRInventoryInterface.h"
#include "PTRPlayerState.generated.h"

/**
*  Player State holds all the important data of the player.
*
*  Note :
*  It may actually make more sens to hold inventory in the character to handle death in MP.
*  But it make more sens for SP because it has consistency on level loading/streaming
*/
UCLASS(ClassGroup=(PTR), Category="Petrichor")
class PETRICHOR_API APTRPlayerState : public APlayerState, public IPTRInventoryInterface
{
	GENERATED_BODY()

public:

	// CTR
	APTRPlayerState( const FObjectInitializer &ObjectInitializer = FObjectInitializer::Get());

	// AActor API
	virtual void BeginPlay() override;
	// \AActor API

	// IPTRInventoryInterface API
	virtual class UPTRInventoryComponent* GetInventoryComponent_Implementation() const override {return PlayerInventory;}
	// \IPTRInventoryInterface API



protected:

	/**
	 * A datatable of items to give to the player at start
	 * @todo we need a way to know if we need this or the data in the save
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Item|Inventory", meta = (AllowedClasses = "DataTable"))
	FSoftObjectPath StartingItem;

	/**
	* A datatable of items to give to the player at start
	* @todo we need a way to know if we need this or the data in the save
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Item|Attributes", meta = (AllowedClasses = "DataTable"))
	FSoftObjectPath AttributesDefinition;

private:

	/**
	 *	Inventory component for this player, stores ammunition, various pickups and whats not
	 *	@todo Save system
	 */
	UPROPERTY(Transient, DuplicateTransient, BlueprintReadOnly, meta=(AllowPrivateAccess))
	class UPTRInventoryComponent* PlayerInventory;

	/**
	 *	Attribute component for this player, give attribute information for UI and gameplay
	 *	@todo add Networking, and automatic interfacing
	 */
	UPROPERTY(Transient, DuplicateTransient, BlueprintReadOnly, meta=(AllowPrivateAccess))
	class UPTRAttributeComponent* PlayerAttributes;


public:

	// default name for override in child classes
	static FName InventoryComponentName;

	// default name for override in child classes
	static FName AttributeComponentName;

	FORCEINLINE class UPTRAttributeComponent* GetAttributeComponent() const {return PlayerAttributes;}


};
