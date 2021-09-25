// Copyright © Noé Perard-Gayot 2021. Licenced under LGPL-3.0-or-later
// You should have received a copy of the GNU Lesser General Public License
// along with Petrichor. If not, see <https://www.gnu.org/licenses/>.

#include "GameEvent/PTRGameEventTypeActions.h"
#include "GameEvent/PTRGameEventBlueprint.h"

#define LOCTEXT_NAMESPACE "PTREditor"

FPTRGameEventTypeActions::FPTRGameEventTypeActions(uint32 InAssetCategory): MyAssetCategory(InAssetCategory)
{

}

FText FPTRGameEventTypeActions::GetName() const
{
	return LOCTEXT("FPTRGameEventTypeActionsName", "PTR Game Event");
}

FColor FPTRGameEventTypeActions::GetTypeColor() const
{
	return FColor::Turquoise;
}

UClass* FPTRGameEventTypeActions::GetSupportedClass() const
{
	return UPTRGameEventBlueprint::StaticClass();
}

uint32 FPTRGameEventTypeActions::GetCategories()
{
	return MyAssetCategory; //affects filters
}

#undef LOCTEXT_NAMESPACE
