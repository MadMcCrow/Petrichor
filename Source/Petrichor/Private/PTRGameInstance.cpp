// Fill out your copyright notice in the Description page of Project Settings.


#include "PTRGameInstance.h"
#include "MoviePlayer.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

void UPTRGameInstance::Init()
{
	Super::Init();

	FCoreUObjectDelegates::PreLoadMap.AddUObject(this, &UPTRGameInstance::BeginLoadingScreen);
	FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &UPTRGameInstance::EndLoadingScreen);
}

void UPTRGameInstance::OpenLevel(TSoftObjectPtr<UWorld> World)
{
	if (World.IsNull())
	{
		OpenLevel(TSoftObjectPtr<UWorld>(GetWorld()));
		return;
	}

	BeginLoadingScreen(World.ToSoftObjectPath().GetAssetPathName().ToString());
	UGameplayStatics::OpenLevel(this,FName(*GetPathFromAsset(World)));
}

void UPTRGameInstance::OpenNextLevel()
{
	UpdateCurrentLevel();
	int32 Found = LegitLevels.Find(CurrentLevel);
	if (Found != INDEX_NONE)
	{
		if (LegitLevels.IsValidIndex(Found+1))
			OpenLevel(LegitLevels[Found + 1]);
		else
			OpenLevel(TSoftObjectPtr<UWorld>(MainMenu));
		return;
	}

	if (LegitLevels.IsValidIndex(0))
	{
		OpenLevel(LegitLevels[0]);
	}

}

void UPTRGameInstance::RestartLevel()
{
	UpdateCurrentLevel();
	OpenLevel(CurrentLevel);
}

void UPTRGameInstance::UpdateCurrentLevel()
{
	CurrentLevel = GetAssetFromPath(UGameplayStatics::GetCurrentLevelName(GetWorld()));
}

void UPTRGameInstance::BeginLoadingScreen(const FString& MapName)
{
	if (!IsRunningDedicatedServer())
	{
		FLoadingScreenAttributes LoadingScreen;
		LoadingScreen.bAutoCompleteWhenLoadingCompletes = false;
		LoadingScreen.WidgetLoadingScreen = FLoadingScreenAttributes::NewTestLoadingScreenWidget();
		GetMoviePlayer()->SetupLoadingScreen(LoadingScreen);
	}
	if (auto WidgetClass = LoadingScreenWidgetClass.TryLoadClass<UUserWidget>())
	{
		LoadingWidget = CreateWidget<UUserWidget>(this, WidgetClass);
		if (LoadingWidget)
		{
			LoadingWidget->AddToViewport();
		}
	}
}

void UPTRGameInstance::EndLoadingScreen(UWorld* InLoadedWorld)
{
	UpdateCurrentLevel();
	if (LoadingWidget)
	{
		LoadingWidget->RemoveFromViewport();
		LoadingWidget = nullptr;
	}
}

TSoftObjectPtr<UWorld> UPTRGameInstance::GetAssetFromPath(const FString& Path)
{
	for (auto itr : LegitLevels)
	{
		if ( GetPathFromAsset(itr) == Path)
		{
			return itr;
		}
	}
	return TSoftObjectPtr<UWorld>(GetWorld());
}

FString UPTRGameInstance::GetPathFromAsset(const TSoftObjectPtr<UWorld>& Asset)
{
	FString PathPart, FilenamePart, ExtensionPart;
	FPaths::Split(Asset.GetLongPackageName(),PathPart, FilenamePart, ExtensionPart);
	return FilenamePart;
}