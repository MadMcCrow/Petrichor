// Copyright © Noé Perard-Gayot 2021. Licenced under LGPL-3.0-or-later
// You should have received a copy of the GNU Lesser General Public License
// along with Petrichor. If not, see <https://www.gnu.org/licenses/>.

#pragma once

#include "AssetTypeActions/AssetTypeActions_Blueprint.h"

class FPTRGameEventTypeActions : public FAssetTypeActions_Blueprint
{
public:
	FPTRGameEventTypeActions(uint32 InAssetCategory);

	// IAssetTypeActions interface
	virtual FText GetName() const override;
	virtual FColor GetTypeColor() const override;
	virtual UClass* GetSupportedClass() const override;

	virtual uint32 GetCategories() override;
	// End of IAssetTypeActions interface

	private:
	uint32 MyAssetCategory;
};
