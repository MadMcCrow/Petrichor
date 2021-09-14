// Copyright © Noé Perard-Gayot 2021. Licenced under LGPL-3.0-or-later
// You should have received a copy of the GNU Lesser General Public License
// along with Petrichor. If not, see <https://www.gnu.org/licenses/>.

#pragma once

#include "CoreMinimal.h"
#include "UObject/PrimaryAssetId.h"
#include "Engine/DataTable.h"
#include "PTRItemTableRow.generated.h"

/**
*	Advanced struct for Setting Inventory in table form
*/
USTRUCT(BlueprintType, Category="Petrichor|Items")
struct FPTRItemTableRow : public FTableRowBase
{
	GENERATED_BODY()

public:

	/**
	*	Unique ID of that Item
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowedClasses="PTRItem"))
	FPrimaryAssetId AssetId;

	/**
	*	Amount stored
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Count;

};
