// Copyright © Noé Perard-Gayot 2021. Licenced under LGPL-3.0-or-later
// You should have received a copy of the GNU Lesser General Public License
// along with Petrichor. If not, see <https://www.gnu.org/licenses/>.

#include "UI/PTRHUD.h"

#include "Engine/Canvas.h"
#include "CanvasItem.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetBlueprintGeneratedClass.h"

#include "UI/PTRHUDWidget.h" // Requiered


APTRHUD::APTRHUD() : Super() , CrosshairSize(128,128)
{

}


void APTRHUD::DrawHUD()
{
	Super::DrawHUD();

	if(Crosshair)
	{
		// find center of the Canvas
		const FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);
		// offset by half the texture's dimensions so that the center of the texture aligns with the center of the Canvas
		const FVector2D CrosshairDrawPosition( (Center.X - CrosshairSize.X/2.f),	(Center.Y + - CrosshairSize.Y/2.f));
		// draw the crosshair
		FCanvasTileItem TileItem(CrosshairDrawPosition,Crosshair->GetRenderProxy(), CrosshairSize );
		TileItem.BlendMode = SE_BLEND_Translucent;
		Canvas->DrawItem( TileItem );
	}
}

void APTRHUD::BeginPlay()
{
	Super::BeginPlay();

	if (auto PC = GetOwningPlayerController())
	{
		for (auto SoftWidgetClassItr : HUDWidgets)
		{
			if (TSubclassOf<UUserWidget> WidgetClass = Cast<UWidgetBlueprintGeneratedClass>(SoftWidgetClassItr.LoadSynchronous()))
			{
				auto HUDWidget = UUserWidget::CreateWidgetInstance(*PC, WidgetClass, MakeUniqueObjectName(this,WidgetClass, NAME_None));
				// TODO : Add ZOrder settings
				HUDWidget->AddToPlayerScreen();
			}
		}
	}

}
