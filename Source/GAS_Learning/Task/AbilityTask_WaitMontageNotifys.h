#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include <Animation/AnimNotifies/AnimNotify.h>
#include "AbilityTask_WaitMontageNotifys.generated.h"



DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMontageDelegate, FName, NotifyName);

/*!
	�ȴ���������Ϣ.
*/
UCLASS()
class GAS_LEARNING_API UAbilityTask_WaitMontageNotifys : public UAbilityTask
{
	GENERATED_BODY()
public:

	UPROPERTY(BlueprintAssignable)
		FOnMontageDelegate OnNotifyBegin;
	UPROPERTY(BlueprintAssignable)
		FOnMontageDelegate OnNotifyEnd;

	/*!�ȴ�Montag�е���Ϣ��ʼ�ͽ���*/
	UFUNCTION(BlueprintCallable, Category = "PingCity|Tasks", meta = (DisplayName = "Wait Montage Notifys", HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
		static UAbilityTask_WaitMontageNotifys* WaitMontageNotifys(UGameplayAbility* OwningAbility);

	virtual void Activate() override;
	virtual void OnDestroy(bool bInOwnerFinished) override;

	bool IsNotifyValid(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointNotifyPayload) const;
protected:

	UPROPERTY()
		int32 MontageInstanceID;

	UFUNCTION()
		void OnNotifyBeginReceived(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointNotifyPayload);

	UFUNCTION()
		void OnNotifyEndReceived(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointNotifyPayload);
};
