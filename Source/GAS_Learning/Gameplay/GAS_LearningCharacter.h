// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"
#include "../AttributeSet/GAS_AttributeSet.h"
#include "GAS_LearningCharacter.generated.h"

USTRUCT(BlueprintType)
struct FMyTestStruct
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite)
	TArray<int32> Values;
};

UCLASS(config=Game)
class AGAS_LearningCharacter : public ACharacter , public IAbilitySystemInterface
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
public:

	UFUNCTION(BlueprintCallable)
	void GetValue1(TArray<int32>& Array);

	UFUNCTION(BlueprintCallable)
	void GetValue(FMyTestStruct& MyTestStruct);

	UFUNCTION(BlueprintCallable)
	void AddValue(int32 Value);

	UFUNCTION(BlueprintCallable)
	void RemoveValue(int32 Index);

	FMyTestStruct a;







	AGAS_LearningCharacter();


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "GameAbilitySystem")
	UGAS_AttributeSet* AttributeSet;
	

	UFUNCTION(BlueprintCallable)
	void GiveAbility(TSubclassOf<UGameplayAbility> InGAClass);
	
	virtual  void BeginPlay() override;

	//当Character被服务器控制时，初始化服务器的GAS组件。
	virtual void PossessedBy(AController* NewController) override;
	
	
	
	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "GameAbilitySystem")
		UAbilitySystemComponent* AbilitySystem;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const;
	
protected:
	

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);


protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface
	
	UPROPERTY(EditDefaultsOnly)
	UDataTable* InputData;
	
public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	UFUNCTION(Server,Reliable)
	void Sever_InitializPassiveSkill();

	UFUNCTION(Server,Reliable)
	void Sever_InitializBindInputAbility();
	
	UPROPERTY(EditDefaultsOnly,meta = (DisplayName = "被动技能"))
	TArray<TSubclassOf<UGameplayAbility>> PassiveSkill;

};

