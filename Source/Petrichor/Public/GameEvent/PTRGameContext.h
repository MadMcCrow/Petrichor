// Copyright © Noé Perard-Gayot 2021. Licenced under LGPL-3.0-or-later
// You should have received a copy of the GNU Lesser General Public License
// along with Petrichor. If not, see <https://www.gnu.org/licenses/>.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "PTRGameContext.generated.h"

/**
 *	Context for GameEvents
 */
UCLASS(BlueprintType, DefaultToInstanced, ClassGroup=(PTR), Category="Petrichor")
class PETRICHOR_API UPTRGameContext : public UObject
{
	GENERATED_BODY()

public:

	// CTR
	UPTRGameContext( const FObjectInitializer &ObjectInitializer = FObjectInitializer::Get());

};
