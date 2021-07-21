// Copyright Epic Games, Inc. All Rights Reserved.

#include "PTRAssetManager.h"

// Static delegate, not clean but gets the job done
FPTROnAssetManagerChange UPTRAssetManager::AssetManagerReady = FPTROnAssetManagerChange();

void UPTRAssetManager::FinishInitialLoading()
{
	Super::FinishInitialLoading();
	AssetManagerReady.Broadcast();
}

bool UPTRAssetManager::IsAssetManagerClass()
{
	if (GEngine != nullptr)
	{
		if (GEngine->AssetManagerClassName.IsValid())
		{
			UClass *SingletonClass = LoadClass<UObject>(nullptr, *GEngine->AssetManagerClassName.ToString());
			return SingletonClass == UPTRAssetManager::StaticClass();
		}
	}
	return false;
}