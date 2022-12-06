// Copyright 2020 Dan Kestranek.


#include "BlueprintTask_AttributeChanged.h"

UBlueprintTask_AttributeChanged* UBlueprintTask_AttributeChanged::ListenForAttributeChange(UAbilitySystemComponent* AbilitySystemComponent, FGameplayAttribute Attribute)
{
	UBlueprintTask_AttributeChanged* WaitForAttributeChangedTask = NewObject<UBlueprintTask_AttributeChanged>();
	WaitForAttributeChangedTask->ASC = AbilitySystemComponent;
	WaitForAttributeChangedTask->AttributeToListenFor = Attribute;

	if (!IsValid(AbilitySystemComponent) || !Attribute.IsValid())
	{
		WaitForAttributeChangedTask->RemoveFromRoot();
		return nullptr;
	}

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attribute).AddUObject(WaitForAttributeChangedTask, &UBlueprintTask_AttributeChanged::AttributeChanged);

	return WaitForAttributeChangedTask;
}

UBlueprintTask_AttributeChanged * UBlueprintTask_AttributeChanged::ListenForAttributesChange(UAbilitySystemComponent * AbilitySystemComponent, TArray<FGameplayAttribute> Attributes)
{
	UBlueprintTask_AttributeChanged* WaitForAttributeChangedTask = NewObject<UBlueprintTask_AttributeChanged>();
	WaitForAttributeChangedTask->ASC = AbilitySystemComponent;
	WaitForAttributeChangedTask->AttributesToListenFor = Attributes;

	if (!IsValid(AbilitySystemComponent) || Attributes.Num() < 1)
	{
		WaitForAttributeChangedTask->RemoveFromRoot();
		return nullptr;
	}

	for (FGameplayAttribute Attribute : Attributes)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attribute).AddUObject(WaitForAttributeChangedTask, &UBlueprintTask_AttributeChanged::AttributeChanged);
	}

	return WaitForAttributeChangedTask;
}

void UBlueprintTask_AttributeChanged::EndTask()
{
	if (IsValid(ASC))
	{
		ASC->GetGameplayAttributeValueChangeDelegate(AttributeToListenFor).RemoveAll(this);

		for (FGameplayAttribute Attribute : AttributesToListenFor)
		{
			ASC->GetGameplayAttributeValueChangeDelegate(Attribute).RemoveAll(this);
		}
	}

	SetReadyToDestroy();
	MarkPendingKill();
}

void UBlueprintTask_AttributeChanged::AttributeChanged(const FOnAttributeChangeData & Data)
{
	OnAttributeChanged.Broadcast(Data.Attribute, Data.NewValue, Data.OldValue);
}