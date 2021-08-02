// Copyright © Noé Perard-Gayot 2021. Licenced under LGPL-3.0-or-later
// You should have received a copy of the GNU Lesser General Public License
// along with Petrichor. If not, see <https://www.gnu.org/licenses/>.

#pragma once

#include "GameFramework/GameModeBase.h"
#include "PTRGameMode.generated.h"

UCLASS(ClassGroup=(PTR), minimalapi)
class APTRGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	APTRGameMode(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
};
