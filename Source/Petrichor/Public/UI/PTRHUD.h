// Copyright © Noé Perard-Gayot 2021. Licenced under LGPL-3.0-or-later
// You should have received a copy of the GNU Lesser General Public License
// along with Petrichor. If not, see <https://www.gnu.org/licenses/>.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PTRHUD.generated.h"

UCLASS(ClassGroup=(PTR), Category="Petrichor|HUD")
class APTRHUD : public AHUD
{
	GENERATED_BODY()

public:
	APTRHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

	/** Spawn the HUD Widget as necessary */
	virtual void BeginPlay() override;

private:
	/** Crosshair asset pointer */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Crosshair", meta = (AllowPrivateAccess="true"))
	class UMaterialInterface* Crosshair;

	/** Crosshair asset pointer */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Crosshair", meta = (AllowPrivateAccess="true"))
	FVector2D CrosshairSize;

	/** Widgets to display on HUD */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Crosshair", meta = (AllowPrivateAccess="true", AllowAbstract="false", DisplayThumbnail = "false"))
	TArray<TSoftClassPtr<class UPTRHUDWidget>> HUDWidgets;

};
