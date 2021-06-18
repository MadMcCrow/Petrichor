// Copyright © Noé Perard-Gayot 2021.

#include "UI/PTRHUD.h"
#include "Engine/Canvas.h"
#include "Engine/Texture2D.h"
#include "TextureResource.h"
#include "CanvasItem.h"


APTRHUD::APTRHUD()
{

}


void APTRHUD::DrawHUD()
{
	Super::DrawHUD();

	if(CrosshairTex)
	{
		// find center of the Canvas
		const FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);

		// offset by half the texture's dimensions so that the center of the texture aligns with the center of the Canvas
		float YOffset = CrosshairTex->GetSizeY() /2.f;
		const FVector2D CrosshairDrawPosition( (Center.X),	(Center.Y + YOffset));

		// draw the crosshair
		FCanvasTileItem TileItem( CrosshairDrawPosition, CrosshairTex->Resource, FLinearColor::White);
		TileItem.BlendMode = SE_BLEND_Translucent;
		Canvas->DrawItem( TileItem );
	}
}