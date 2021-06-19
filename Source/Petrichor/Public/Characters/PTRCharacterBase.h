// Copyright © Noé Perard-Gayot 2021.

#pragma once

#include "GameFramework/Character.h"
#include "PTRCharacterBase.generated.h"


/**
 *	Base character :
 *	- handles movement
 *	- Handle meshes
 */
UCLASS(Abstract, NotBlueprintable, config=Game)
class APTRCharacterBase : public ACharacter
{
	GENERATED_BODY()


public:

	APTRCharacterBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
protected:

	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

private:

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category="Mesh", meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* FirstPersonMesh;

	/** Pawn mesh: Third person mesh : Whole body */
	UPROPERTY(VisibleDefaultsOnly, Category="Mesh", meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* ThirdPersonMesh;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FirstPersonCameraComponent;



protected:
	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera")
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera")
	float BaseLookUpRate;


protected:

	/** Plug code to use weapons here */
	virtual void OnFire();

	virtual void Crouch();
	virtual void StopCrouch();

	// Movement functions
	virtual void MoveForward(float Val);
	virtual void MoveRight(float Val);
	virtual void TurnAtRate(float Rate);
	virtual void LookUpAtRate(float Rate);


public:

	// inline getters
	FORCEINLINE class USkeletalMeshComponent* GetFirstPersonMesh() const		{ return FirstPersonMesh; }
	FORCEINLINE class USkeletalMeshComponent* GetThirdPersonMesh() const		{ return ThirdPersonMesh; }
	FORCEINLINE class UCameraComponent* GetFirstPersonCameraComponent() const	{ return FirstPersonCameraComponent; }

	/** Static names for components*/
	static FName FirstPersonMeshName;
	static FName ThirdPersonMeshName;
	static FName FirstPersonCameraName;

};