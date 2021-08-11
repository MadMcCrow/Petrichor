// Copyright © Noé Perard-Gayot 2021. Licenced under LGPL-3.0-or-later
// You should have received a copy of the GNU Lesser General Public License
// along with Petrichor. If not, see <https://www.gnu.org/licenses/>.

#pragma once

#include "CoreMinimal.h"
#include "Factories/BlueprintFactory.h"
#include "PTRGameEventFactory.generated.h"


/**
 *	Helper for Creating GameEvent Blueprints in Editor
 */
UCLASS(MinimalAPI, hidecategories=Object, collapsecategories)
class UPTRGameEventFactory : public UFactory
{
	GENERATED_BODY()
public:
	// Default CTR.
	UPTRGameEventFactory();

	// UFactory interface
	virtual FText GetDisplayName() const override;
	virtual uint32 GetMenuCategories() const override;
	virtual FText GetToolTip() const override;
	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn, FName CallingContext) override;
	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
	virtual bool ConfigureProperties() override;
	virtual FString GetDefaultNewAssetName() const override;
	virtual FName GetNewAssetThumbnailOverride() const override;
	virtual bool ShouldShowInNewMenu() const override { return true; }
	virtual bool CanCreateNew() const override {return true;}
	// End of UFactory interface


protected:

	UPROPERTY(EditAnywhere, Category = PTRGameEventFactory, meta = (AllowAbstract = ""))
	UClass* ParentClass;

};
