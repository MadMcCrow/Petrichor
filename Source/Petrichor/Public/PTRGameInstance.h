// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PTRGameInstance.generated.h"

/**
 *	PTR Game Instance.
 *	Most of these system should be moved to a subsystem
 */
UCLASS(ClassGroup=(PTR), minimalapi)
class UPTRGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	virtual void Init() override;


	/**
	 *	Open any level based on soft ObjectPtr
	 *	@todo : replace with FSoftObjectPath
	 *	@todo : Multiplayer networking
	 *	@todo : implement level streaming
	 */
	UFUNCTION(BlueprintCallable, Category="Level")
	void OpenLevel(TSoftObjectPtr<UWorld> World);

	/**
	 *	Will open the next level in the list of legit Levels
	 */
	UFUNCTION(BlueprintCallable, Category="Level")
	void OpenNextLevel();

	/**
	 *	Will restart current level
	 */
	UFUNCTION(BlueprintCallable, Category="Level")
	void RestartLevel();

	/**
	 *	Will find out what level we are in and update our private value
	 */
	UFUNCTION(BlueprintCallable, Category="Level")
	void UpdateCurrentLevel();


protected:


	/**
	 *	Levels to play in order
	 *	@todo : replace by data Asset
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSoftObjectPtr<UWorld>> LegitLevels;

	/**
	 *	The main menu level for the game
	 *	@todo : replace by data Asset
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowedClasses="World"))
	FSoftObjectPath MainMenu;

	/**
	 *	LoadingScreenWidgetClass
	 *	Loading screen widget to spawn
	 *	@todo : implement Loading screen logic
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowedClasses="UUserWidget"))
	FSoftClassPath LoadingScreenWidgetClass;

	/**
	 *	@fn BeginLoadingScreen
	 *	@todo : implement Loading screen logic
	 */
	UFUNCTION()
	virtual void BeginLoadingScreen(const FString& MapName);

	/**
	 *	@fn EndLoadingScreen
	 *	@todo : implement Loading screen logic
	 */
	UFUNCTION()
	virtual void EndLoadingScreen(UWorld* InLoadedWorld);


private:

	/**
	 *	Current level as updated by @see UpdateCurrentLevel
	 */
	UPROPERTY(Transient)
	TSoftObjectPtr<UWorld> CurrentLevel;

	/**
	 *	Spawned loading screen widget
	 */
	UPROPERTY(Transient)
	UUserWidget* LoadingWidget;


	// simple helpers

	/** Helper for map asset from path. Should be be made to use asset manager */
	TSoftObjectPtr<UWorld> GetAssetFromPath(const FString& Path);

	/** Helper for map path from asset. Should be be made to use asset manager */
	FString GetPathFromAsset(const TSoftObjectPtr<UWorld>& Asset);
};