// Copyright © Noé Perard-Gayot 2021. Licenced under LGPL-3.0-or-later
// You should have received a copy of the GNU Lesser General Public License
// along with Petrichor. If not, see <https://www.gnu.org/licenses/>.

#include "Items/PTRItem.h"




UPTRItem::UPTRItem(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	UpdateItemInternal();
}


void UPTRItem::PreSave(const ITargetPlatform* TargetPlatform)
{
#if WITH_EDITOR
	UpdateItemInternal();
#endif // WITH_EDITOR
}

void UPTRItem::UpdateItemInternal()
{
	InternalName = GetFName();
	AssetType = FName("Item");
}
