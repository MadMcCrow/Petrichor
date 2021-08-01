// Copyright © Noé Perard-Gayot 2021.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "PTRGameEvent.generated.h"


DECLARE_LOG_CATEGORY_EXTERN(LogPTRGameEvent, Log, All);

class AActor;

/**
 *	Player State stores Player information. this is transferred between maps.
 */
UCLASS(ClassGroup=(PTR), Category="Petrichor|GameEvent", DefaultToInstanced, Blueprintable, EditInlineNew)
class PETRICHOR_API UPTRGameEvent : public UObject
{
	GENERATED_BODY()

public:

	// CTR
	UPTRGameEvent( const FObjectInitializer &ObjectInitializer = FObjectInitializer::Get());

	/**
	 *	Start event
	 *	It will try to start event on both server and client
	 */
	UFUNCTION(BlueprintCallable)
	void StartEvent(AActor * Source, AActor* Target);


	/**
	 *	OnServerEventStart
	 *	Server Only event.
	 */
	UFUNCTION(BlueprintNativeEvent, BlueprintAuthorityOnly, Category = "GameEvent|Server")
	void OnServerEventStart();
	virtual void OnServerEventStart_Implementation();

	/**
	*	OnClientEventStart
	*	Server Only event.
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCosmetic, Category = "GameEvent|Server")
	void OnClientEventStart();
	virtual void OnClientEventStart_Implementation();

	/**
	*	OnEventStart
	*	Server Only event.
	*/
	UFUNCTION(BlueprintNativeEvent, Category = "GameEvent|Server")
	void OnEventStart();
	virtual void OnEventStart_Implementation();

	/**
	*	GetSource
	*	return Source/Instigator for scripting
	*/
	UFUNCTION(BlueprintPure, Category = "GameEvent",  meta = (HideSelfPin = "true", CompactNodeTitle = "Source"))
	virtual AActor* GetSource() const;


	/**
	*	GetTarget
	*	return Target for scripting
	*/
	UFUNCTION(BlueprintPure, Category = "GameEvent",  meta = (HideSelfPin = "true",  CompactNodeTitle = "Target"))
	virtual AActor* GetTarget() const;




protected:

	/**
	 *	Start event on server
	 */
	UFUNCTION(Server, Reliable, WithValidation)
	void Net_StartServerEvent(AActor * Source, AActor* Target);
	void Net_StartServerEvent_Implementation(AActor * Source, AActor* Target);
	bool Net_StartServerEvent_Validate(AActor * Source, AActor* Target) {return true;}

	/**
	*	Start event on client
	*/
	UFUNCTION(Client, Reliable, WithValidation)
	void Net_StartClientEvent(AActor * Source, AActor* Target);
	void Net_StartClientEvent_Implementation(AActor * Source, AActor* Target);
	bool Net_StartClientEvent_Validate(AActor * Source, AActor* Target) {return true;}

	/**
	*	Start event on client
	*/
	UFUNCTION(NetMulticast, Reliable, WithValidation)
	void Net_StartAllEvent(AActor * Source, AActor* Target);
	void Net_StartAllEvent_Implementation(AActor * Source, AActor* Target);
	bool Net_StartAllEvent_Validate(AActor * Source, AActor* Target) {return true;}

private:
	/** Source of this event and who will be responsible for handling it */
	UPROPERTY(Transient, DuplicateTransient, BlueprintGetter="GetSource")
	AActor * Instigator;

	/** Target for this Event, might be equal to Instigator */
	UPROPERTY(Transient, DuplicateTransient, BlueprintGetter="GetTarget")
	AActor * TargetActor;

};