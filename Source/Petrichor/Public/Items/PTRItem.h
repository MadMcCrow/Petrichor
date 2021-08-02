// Copyright © Noé Perard-Gayot 2021. Licenced under LGPL-3.0-or-later
// You should have received a copy of the GNU Lesser General Public License
// along with Petrichor. If not, see <https://www.gnu.org/licenses/>.

#pragma once

#include "Engine/DataAsset.h"
#include "PTRItem.generated.h"


UCLASS( ClassGroup=(PTR), Category="Petrichor|Items")
class PETRICHOR_API UPTRItem : public UPrimaryDataAsset
{
    GENERATED_BODY()

public:
    // Default CTR
    UPTRItem(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

    // UPrimaryDataAsset API
    virtual void PreSave(const ITargetPlatform* TargetPlatform) override;
    // \UPrimaryDataAsset API

    /**
     *  Reference this in your asset manager
     */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Item|System")
    FPrimaryAssetType AssetType;

    /**
     *  The unique name for this item
     */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Item|System")
    FName InternalName;

    // uniqueID used for referencing this
    virtual FPrimaryAssetId GetPrimaryAssetId() const override
    {
        return FPrimaryAssetId(AssetType, InternalName);
    }

protected:

    /** Name displayed to the user. */
    UPROPERTY(EditAnywhere, blueprintReadOnly, Category="Item|Display")
    FText DisplayName;

    /** Extra Info we can display to the user. */
    UPROPERTY(EditAnywhere, blueprintReadOnly, Category="Item|Display")
    FText Description;

private:
    /** Update AssetType and InternalName */
    void UpdateItemInternal();
};
