// Copyright © Noé Perard-Gayot 2021.

#include "UI/PTRHUD.h"
#include "Engine/Canvas.h"
#include "Engine/Texture2D.h"
#include "TextureResource.h"
#include "CanvasItem.h"


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