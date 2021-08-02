// Copyright © Noé Perard-Gayot 2021. Licenced under LGPL-3.0-or-later
// You should have received a copy of the GNU Lesser General Public License
// along with Petrichor. If not, see <https://www.gnu.org/licenses/>.

#include "PTRGameMode.h"
#include "UI/PTRHUD.h"
#include "Characters/PTRCharacter.h"
#include "Player/PTRPlayerState.h"

APTRGameMode::APTRGameMode(const FObjectInitializer& ObjectInitializer)
{
	DefaultPawnClass = APTRCharacter::StaticClass();
	PlayerStateClass = APTRPlayerState::StaticClass();
	HUDClass = APTRHUD::StaticClass();
}
