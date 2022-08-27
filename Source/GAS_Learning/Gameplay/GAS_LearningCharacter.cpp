// Copyright Epic Games, Inc. All Rights Reserved.

#include "GAS_LearningCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Abilities/GameplayAbility_CharacterJump.h"
#include "GAS_Learning/GA/CommonType.h"

//////////////////////////////////////////////////////////////////////////
// AGAS_LearningCharacter

AGAS_LearningCharacter::AGAS_LearningCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)


	//ASC = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystem");
	AbilitySystem = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystem");
	AttributeSet = CreateDefaultSubobject<UGAS_AttributeSet>("AttributeSet");
}

void AGAS_LearningCharacter::GiveAbility(TSubclassOf<UGameplayAbility> InGAClass)
{
	AbilitySystem->GiveAbility(FGameplayAbilitySpec(InGAClass));
}

//	bool TryActivateAbility(FGameplayAbilitySpecHandle AbilityToActivate, bool bAllowRemoteActivation = true);


void AGAS_LearningCharacter::BeginPlay()
{
	Super::BeginPlay();
	AttributeSet->InitHealth(100);
	AttributeSet->InitMaxHealth(150);
	AttributeSet->InitSpeed(400);
	GetCharacterMovement()->MaxWalkSpeed = AttributeSet->GetSpeed();
}

void AGAS_LearningCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	AbilitySystem->InitAbilityActorInfo(this, this);
}


UAbilitySystemComponent* AGAS_LearningCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystem;
}

//////////////////////////////////////////////////////////////////////////
// Input

void AGAS_LearningCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	//PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	//PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &AGAS_LearningCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AGAS_LearningCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AGAS_LearningCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AGAS_LearningCharacter::LookUpAtRate);


	if(IsValid(AbilitySystem))
	{
		AbilitySystem->BindAbilityActivationToInputComponent(PlayerInputComponent,
			FGameplayAbilityInputBinds(
				FString("Confirm"),
				FString("Cancel"),
				FString("GA_InputID")
				));
	}
	
}

void AGAS_LearningCharacter::Sever_InitializBindInputAbility_Implementation()
{
	//AbilitySystem->GiveAbility(FGameplayAbilitySpec(UGameplayAbility_CharacterJump::StaticClass(),1,static_cast<int8>(GA_InputID::Jump),this));
	
	if (InputData)
	{
		TArray<FBindInputID*> AllInput;  
		InputData->GetAllRows(TEXT("AnimTable"), AllInput/*TArray<FCharacterAnimTable*>*/);

		for(const auto& r : AllInput)
		{
			if(r->SkillClass)
			{
				AbilitySystem->GiveAbility(FGameplayAbilitySpec(r->SkillClass,1,static_cast<INT8>(r->InputID)));
			}
		}
	}
}

void AGAS_LearningCharacter::Sever_InitializPassiveSkill_Implementation()
{
	for(const auto& r: PassiveSkill)
	{
		AbilitySystem->GiveAbility(FGameplayAbilitySpec(r));
	}
}


void AGAS_LearningCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AGAS_LearningCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AGAS_LearningCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AGAS_LearningCharacter::MoveRight(float Value)
{
	if ( (Controller != nullptr) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}
