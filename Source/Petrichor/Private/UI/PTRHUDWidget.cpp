// Copyright © Noé Perard-Gayot 2021. Licenced under LGPL-3.0-or-later
// You should have received a copy of the GNU Lesser General Public License
// along with Petrichor. If not, see <https://www.gnu.org/licenses/>.

#include "UI/PTRHUDWidget.h"
#include "Characters/PTRCharacter.h"
#include "Player/PTRPlayerState.h"

class APTRCharacter* UPTRHUDWidget::GetPTRCharacter() const
{
	if (GetOwningPlayer())
	{
		return Cast<APTRCharacter>(GetOwningPlayer()->GetPawn());
	}
	return nullptr;
}

APTRPlayerState* UPTRHUDWidget::GetPTRPlayerState() const
{
	if (GetOwningPlayer())
	{
		return GetOwningPlayer()->GetPlayerState<APTRPlayerState>();
	}
	return nullptr;
}

void UPTRHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();
}
