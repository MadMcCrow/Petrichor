// Copyright © Noé Perard-Gayot 2021. Licenced under LGPL-3.0-or-later
// You should have received a copy of the GNU Lesser General Public License
// along with Petrichor. If not, see <https://www.gnu.org/licenses/>.

#include "Characters/PTRCharacterBase.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Characters/PTRCharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/InputSettings.h"


FName APTRCharacterBase::FirstPersonMeshName	= TEXT("FirstPersonMesh");
FName APTRCharacterBase::ThirdPersonMeshName 	= TEXT("ThirdPersonMesh");
FName APTRCharacterBase::FirstPersonCameraName	= TEXT("FirstPersonCamera");

APTRCharacterBase::APTRCharacterBase(const FObjectInitializer& ObjectInitializer) : Super(
	ObjectInitializer
	.DoNotCreateDefaultSubobject(ACharacter::MeshComponentName)
	.SetDefaultSubobjectClass(CharacterMovementComponentName, UPTRCharacterMovementComponent::StaticClass())
	)
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(44.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Create a CameraComponent
	FirstPersonCameraComponent = ObjectInitializer.CreateDefaultSubobject<UCameraComponent>(this, FirstPersonCameraName);
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, BaseEyeHeight)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	FirstPersonMesh = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this, FirstPersonMeshName);
	FirstPersonMesh->SetOnlyOwnerSee(true);
	FirstPersonMesh->SetupAttachment(FirstPersonCameraComponent);
	FirstPersonMesh->bCastDynamicShadow = false;
	FirstPersonMesh->CastShadow = false;

	FirstPersonMesh->SetRelativeRotation(FRotator(1.9f, -19.19f, 5.2f));
	FirstPersonMesh->SetRelativeLocation(FVector(-0.5f, -4.4f, -155.7f));

	ThirdPersonMesh = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this, ThirdPersonMeshName);
	ThirdPersonMesh->SetOwnerNoSee(true);
	ThirdPersonMesh->SetupAttachment(GetCapsuleComponent());
	ThirdPersonMesh->bCastDynamicShadow = false;
	ThirdPersonMesh->CastShadow = true;

	// Nav Agent properties
	// Todo : Make a function/system to set this
	FNavAgentProperties NavAgentProperties;
	NavAgentProperties.AgentRadius	= 48.f;
	NavAgentProperties.AgentHeight	= 12.f;
	NavAgentProperties.bCanCrouch	= true;
	NavAgentProperties.bCanJump		= true;
	NavAgentProperties.bCanSwim		= true;
	GetCharacterMovement()->NavAgentProps = NavAgentProperties;

	// crouching takes 1s;
	CrouchedMovementDuration = 0.1f;
	CrouchedEyeHeight = BaseEyeHeight *0.7f;
}

void APTRCharacterBase::RecalculateBaseEyeHeight()
{
	// Skip ACharacter Base Height stupid calculation
	APawn::RecalculateBaseEyeHeight();
}

void APTRCharacterBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// update FPS Camera Height Location
	if (GetFirstPersonCameraComponent())
	{
		UpdateCameraLocation(DeltaSeconds);
	}
}

void APTRCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	CrouchedCurrentTime = 0.f;
}

void APTRCharacterBase::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);

	// Bind jump events
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &APTRCharacterBase::StartCrouch);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &APTRCharacterBase::StopCrouch);

	// Bind fire event
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APTRCharacterBase::OnFire);

	// Bind movement events
	PlayerInputComponent->BindAxis("MoveForward", 	this,	&APTRCharacterBase::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", 	this,	&APTRCharacterBase::MoveRight);
	PlayerInputComponent->BindAxis("Turn", 			this, 	&APTRCharacterBase::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", 		this, 	&APTRCharacterBase::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp",		this,	&APTRCharacterBase::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate",	this,	&APTRCharacterBase::LookUpAtRate);
}

void APTRCharacterBase::OnFire()
{
	// nothing to see here
}

void APTRCharacterBase::StartCrouch()
{
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->bWantsToCrouch = true;
	}
}

void APTRCharacterBase::StopCrouch()
{
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->bWantsToCrouch = false;
	}
}

void APTRCharacterBase::UpdateCameraLocation(float DeltaTime)
{
	CrouchedCurrentTime = FMath::Clamp( CrouchedCurrentTime + ((bIsCrouched ? 1 : -1) * DeltaTime / CrouchedMovementDuration) , 0.f,1.f);
	const float DeltaLocation = FMath::Lerp(BaseEyeHeight, CrouchedEyeHeight, CrouchedCurrentTime);

	if (FirstPersonCameraComponent && GetCapsuleComponent())
	{
		const FVector CameraLocation = FirstPersonCameraComponent->GetRelativeLocation();
		const float ZOffset = GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
		FirstPersonCameraComponent->SetRelativeLocation(FVector(CameraLocation.X, CameraLocation.Y, (2 * DeltaLocation) -ZOffset));
	}
}

void APTRCharacterBase::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void APTRCharacterBase::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void APTRCharacterBase::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void APTRCharacterBase::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}
