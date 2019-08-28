// Copyright 2019 - Now Salty Panda Studios. All Rights reserved.


#include "BTT_SetBlackboardProperty.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Bool.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Int.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Float.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_String.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Name.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Rotator.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Enum.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Class.h"
#include <BrainComponent.h>
#include "Runtime/AIModule/Classes/AIController.h"
#include "Runtime/AIModule/Classes/BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTT_SetBlackboardProperty::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	UBlackboardComponent& BlackboardComp = *OwnerComp.GetBlackboardComponent();

	if (BlackboardComp.GetKeyType(BlackboardComp.GetKeyID(Key.SelectedKeyName)))
	{
		UObject* ClassObject = nullptr;
		ClassObject = BlackboardComp.GetKeyType(BlackboardComp.GetKeyID(Key.SelectedKeyName))->GetDefaultObject();

		if (UBlackboardKeyType_Bool * BoolType = Cast<UBlackboardKeyType_Bool>(ClassObject))
		{
			BlackboardComp.SetValueAsBool(Key.SelectedKeyName, BlackboardValue.BoolValue);
		}

		else if (UBlackboardKeyType_String * StringType = Cast<UBlackboardKeyType_String>(ClassObject))
		{
			BlackboardComp.SetValueAsString(Key.SelectedKeyName, BlackboardValue.StringValue);
		}

		else if (UBlackboardKeyType_Int * IntType = Cast<UBlackboardKeyType_Int>(ClassObject))
		{
			BlackboardComp.SetValueAsInt(Key.SelectedKeyName, BlackboardValue.IntValue);
		}

		else if (UBlackboardKeyType_Float * FloatType = Cast<UBlackboardKeyType_Float>(ClassObject))
		{
			BlackboardComp.SetValueAsFloat(Key.SelectedKeyName, BlackboardValue.FloatValue);
		}

		else 	if (UBlackboardKeyType_Name * NameType = Cast<UBlackboardKeyType_Name>(ClassObject))
		{
			BlackboardComp.SetValueAsName(Key.SelectedKeyName, BlackboardValue.NameValue);
		}

		else if (UBlackboardKeyType_Enum * EnumType = Cast<UBlackboardKeyType_Enum>(ClassObject))
		{
			BlackboardComp.SetValueAsEnum(Key.SelectedKeyName, BlackboardValue.EnumValue);
		}

		else if (UBlackboardKeyType_Class * ClassType = Cast<UBlackboardKeyType_Class>(ClassObject))
		{
			BlackboardComp.SetValueAsClass(Key.SelectedKeyName, BlackboardValue.ClassValue);
		}
		else
		{
			return bReturnSuccessIfInvalid ? EBTNodeResult::Succeeded : EBTNodeResult::Failed;
		}
	}
	else
	{
		return bReturnSuccessIfInvalid ? EBTNodeResult::Succeeded : EBTNodeResult::Failed;
	}

	return EBTNodeResult::Succeeded;
}

EBTNodeResult::Type UBTT_SetBlackboardProperty::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::AbortTask(OwnerComp, NodeMemory);
	return EBTNodeResult::Succeeded;
}

#if WITH_EDITOR
void UBTT_SetBlackboardProperty::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	FName PropertyName = (PropertyChangedEvent.Property != NULL) ? PropertyChangedEvent.Property->GetFName() : NAME_None;
	if (PropertyName == FName("SelectedKeyType"))
	{
		if(OnChanged.IsBound())
		OnChanged.Execute();
	}

	UpdateName();
}

void UBTT_SetBlackboardProperty::PostEditChangeChainProperty(struct FPropertyChangedChainEvent& PropertyChangedEvent)
{
	Super::PostEditChangeChainProperty(PropertyChangedEvent);

	FName PropertyName = (PropertyChangedEvent.Property != NULL) ? PropertyChangedEvent.Property->GetFName() : NAME_None;
	if (PropertyName == FName("SelectedKeyType"))
	{
		if (OnChanged.IsBound())
		OnChanged.Execute();
	}

	UpdateName();
}

void UBTT_SetBlackboardProperty::UpdateName()
{
	FString Value = "";

	if (Key.SelectedKeyType)
	{
		UObject* ClassObject = nullptr;
		ClassObject = Key.SelectedKeyType->GetDefaultObject();

		if (UBlackboardKeyType_Bool * BoolType = Cast<UBlackboardKeyType_Bool>(ClassObject))
		{
			Value = BlackboardValue.BoolValue ? "True" : "False";
		}

		else if (UBlackboardKeyType_String * StringType = Cast<UBlackboardKeyType_String>(ClassObject))
		{
			//Only return first 30.. we don't have an entire book to be displayed in the node name :)
			Value = BlackboardValue.StringValue.Left(30);
		}

		else if (UBlackboardKeyType_Int * IntType = Cast<UBlackboardKeyType_Int>(ClassObject))
		{
			Value = FString::FromInt(BlackboardValue.IntValue);
		}

		else if (UBlackboardKeyType_Float * FloatType = Cast<UBlackboardKeyType_Float>(ClassObject))
		{
			Value = FString::SanitizeFloat(BlackboardValue.FloatValue);
		}

		else 	if (UBlackboardKeyType_Name * NameType = Cast<UBlackboardKeyType_Name>(ClassObject))
		{
			Value = BlackboardValue.NameValue.ToString();
		}

		else if (UBlackboardKeyType_Enum * EnumType = Cast<UBlackboardKeyType_Enum>(ClassObject))
		{
			Value = FString::FromInt((int32)BlackboardValue.EnumValue);
		}

		else if (UBlackboardKeyType_Class * ClassType = Cast<UBlackboardKeyType_Class>(ClassObject))
		{
			Value = BlackboardValue.ClassValue ? BlackboardValue.ClassValue->GetName() : "null";
		}
	}

	NodeName = "Set" + Key.SelectedKeyName.ToString() + " to " + Value;
}
#endif
