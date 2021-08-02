// Copyright © Noé Perard-Gayot 2021. Licenced under LGPL-3.0-or-later
// You should have received a copy of the GNU Lesser General Public License
// along with Petrichor. If not, see <https://www.gnu.org/licenses/>.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "PTRAIController.generated.h"

/**
 *	Base AI Controller for AI in Petrichor
 */
UCLASS(ClassGroup=(PTR), Category="Petrichor")
class PETRICHOR_API APTRAIController : public AAIController
{
	GENERATED_BODY()

public:

	// CTR
	APTRAIController( const FObjectInitializer &ObjectInitializer = FObjectInitializer::Get());
};
