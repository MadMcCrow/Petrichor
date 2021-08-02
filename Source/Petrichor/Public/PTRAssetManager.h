// Copyright © Noé Perard-Gayot 2021. Licenced under LGPL-3.0-or-later
// You should have received a copy of the GNU Lesser General Public License
// along with Petrichor. If not, see <https://www.gnu.org/licenses/>.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "PTRAssetManager.generated.h"

DECLARE_MULTICAST_DELEGATE(FPTROnAssetManagerChange);

/**
 *	@class UPTRAssetManager
 *	Asset Manager with some extra steps.
 *		- Add an event for when ready
 */
UCLASS(ClassGroup=(PTR), config=Game, minimalapi, Category="PTR")
class UPTRAssetManager : public UAssetManager
{
	GENERATED_BODY()

public:
	// UAssetManager API
	virtual void FinishInitialLoading() override;
	// \UAssetManager API

	/**
	 *	Delegate called when all initialization is done
	 *	- Use this if you need to be sure the asset manager is ready to use
	 *	@note :this delegate will always exist due to being static
	 *	There might be better ways of doing this, but I haven't found them
	 */
	static FPTROnAssetManagerChange AssetManagerReady;

	static bool IsAssetManagerClass();



};
