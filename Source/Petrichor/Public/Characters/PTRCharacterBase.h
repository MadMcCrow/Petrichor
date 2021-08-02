// Copyright © Noé Perard-Gayot 2021. Licenced under LGPL-3.0-or-later
// You should have received a copy of the GNU Lesser General Public License
// along with Petrichor. If not, see <https://www.gnu.org/licenses/>.

#pragma once

#include "GameFramework/Character.h"
#include "PTRCharacterBase.generated.h"


/**
 *	Base character :
 *	- handles movement
 *	- Handle meshes
 */
UCLASS(ClassGroup=(PTR), Abstract, NotBlueprintable, config=Game)
class APTRCharacterBase : public ACharacter
{
	GENERATED_BODY()


public:

	APTRCharacterBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void RecalculateBaseEyeHeight() override;

	virtual void Tick(float DeltaSeconds) override;

protected:

	virtual void BeginPlay() override;
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

	/** Default crouched eye height */
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category= "Camera")
	float CrouchedMovementDuration;

private:

	UPROPERTY(Transient, DuplicateTransient)
	float CrouchedCurrentTime;

protected:

	/** Plug code to use weapons here */
	virtual void OnFire();

	virtual void StartCrouch();
	virtual void StopCrouch();

	virtual void UpdateCameraLocation(float DeltaSeconds);

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
