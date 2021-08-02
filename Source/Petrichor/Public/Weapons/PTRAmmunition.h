// Copyright © Noé Perard-Gayot 2021. Licenced under LGPL-3.0-or-later
// You should have received a copy of the GNU Lesser General Public License
// along with Petrichor. If not, see <https://www.gnu.org/licenses/>.

#pragma once

#include "Items/PTRItem.h"
#include "PTRAmmunition.generated.h"


/**
 *	Ammunition are just a default class storing information about that ammo
 *	They are used to find out if you have ammo in your inventory
 */
UCLASS(ClassGroup=(PTR), Category="Petrichor|Items")
class PETRICHOR_API UPTRAmmunition : public UPTRItem
{
	GENERATED_BODY()

};
