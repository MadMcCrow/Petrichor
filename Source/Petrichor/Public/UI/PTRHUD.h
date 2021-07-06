// Copyright © Noé Perard-Gayot 2021.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PTRHUD.generated.h"

UCLASS()
class APTRHUD : public AHUD
{
	GENERATED_BODY()

public:
	APTRHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Crosshair", meta = (AllowPrivateAccess="true"))
	class UMaterialInterface* Crosshair;

	/** Crosshair asset pointer */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Crosshair", meta = (AllowPrivateAccess="true"))
	FVector2D CrosshairSize;
};