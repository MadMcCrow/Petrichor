// Copyright © Noé Perard-Gayot 2021.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PTRInventoryComponent.generated.h"


USTRUCT( BlueprintType, Category="Petrichor|Items")
struct FPTRInventoryItem
{
    GENERATED_BODY()

    /** Asset Unique ID */
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FPrimaryAssetId ItemID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FSoftObjectPath ItemAssetPath;

	friend inline uint32 GetTypeHash(const FPTRInventoryItem& Key)
	{
		uint32 Hash = 0;
		Hash = HashCombine(Hash, GetTypeHash(Key.ItemID));
		return Hash;
	}

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Count;
};


UCLASS(ClassGroup=(PTR), config=Game, Category="Petrichor|Items")
class UPTRInventoryComponent : public UActorComponent
{
    GENERATED_BODY()

public:

    UPTRInventoryComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

private:

    UPROPERTY(Transient, VisibleAnywhere, Category="Inventory")
    TSet<FPTRInventoryItem> Items;

};