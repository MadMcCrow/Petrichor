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
	UFUNCTION(BlueprintCallable, Category = "GameEvent")
	void StartEvent(AActor * Source, AActor* Target);

	/**
	*	OnEventStart
	*	Specify that this event is done
	*/
	UFUNCTION(BlueprintCallable, Category = "GameEvent")
	void EndEvent();

	/**
	 *	OnServerEventStart
	 *	Server Only event.
	 */
	UFUNCTION(BlueprintNativeEvent, BlueprintAuthorityOnly, Category = "GameEvent|Server")
	void OnServerEventStart();
	virtual void OnServerEventStart_Implementation();

	/**
	*	OnClientEventStart
	*	Owning Client Only event.
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCosmetic, Category = "GameEvent|Client")
	void OnClientEventStart();
	virtual void OnClientEventStart_Implementation();

	/**
	*	OnEventStart
	*	Other Clients, Server and Owning client
	*/
	UFUNCTION(BlueprintNativeEvent, Category = "GameEvent|Multicast")
	void OnEventStart();
	virtual void OnEventStart_Implementation();

	/**
	*	OnEventStart
	*	Other Clients, Server and Owning client
	*/
	UFUNCTION(BlueprintNativeEvent, Category = "GameEvent|Multicast")
	void OnEventEnd();
	virtual void OnEventEnd_Implementation();



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
	*	Start event on all clients
	*/
	UFUNCTION(NetMulticast, Reliable, WithValidation)
	void Net_StartAllEvent(AActor * Source, AActor* Target);
	void Net_StartAllEvent_Implementation(AActor * Source, AActor* Target);
	bool Net_StartAllEvent_Validate(AActor * Source, AActor* Target) {return true;}

	/**
	 *	End event on all clients
	 */
	UFUNCTION(NetMulticast, Reliable, WithValidation)
	void Net_EndAllEvent();
	void Net_EndAllEvent_Implementation();
	bool Net_EndAllEvent_Validate() {return true;}


protected:

	/**
	 *	This allow to prevent server function to be requested by clients
	 *	if true the client will request the server to run the function
	 *	if false the client will only run it's simulation, never asking for server to do the same
	 *	this is useful for Weapons where the weapon component will trigger the Game Event
	 *	on both the server and client manually
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="GameEvent")
	bool bShouldCallServerOnClient;

	/**
	 *	This allows us to call separately on clients and server and
	 *	let the client reconcile itself with the server at the end
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="GameEvent")
	bool bServerShouldTriggerEventOnOwningClient;


private:
	/** Source of this event and who will be responsible for handling it */
	UPROPERTY(Transient, DuplicateTransient, BlueprintGetter="GetSource")
	AActor * Instigator;

	/** Target for this Event, might be equal to Instigator */
	UPROPERTY(Transient, DuplicateTransient, BlueprintGetter="GetTarget")
	AActor * TargetActor;

};
