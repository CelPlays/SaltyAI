// Copyright 2019 - Now Salty Panda Studios. All Rights reserved.

#include "BTT_ExecuteFunction.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "Runtime/AIModule/Classes/BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTT_ExecuteFunction::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	UBlackboardComponent& BlackboardComp = *OwnerComp.GetBlackboardComponent();
	UObject* Object = BlackboardComp.GetValueAsObject(Target.SelectedKeyName);

	if (!Object)
	{
		return bReturnSuccessIfInvalid ? EBTNodeResult::Succeeded : EBTNodeResult::Failed;
	}

	UFunction* Func = Object->FindFunction(FName(*FunctionContext.FunctionToExecute));

	if (Func)
	{
		Object->ProcessEvent(Func, nullptr);
	}
	else
	{
		return bReturnSuccessIfInvalid ? EBTNodeResult::Succeeded : EBTNodeResult::Failed;
	}

	return EBTNodeResult::Succeeded;
}

EBTNodeResult::Type UBTT_ExecuteFunction::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::AbortTask(OwnerComp, NodeMemory);
	return EBTNodeResult::Succeeded;
}

#if WITH_EDITOR
void UBTT_ExecuteFunction::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	UpdateName();
}

void UBTT_ExecuteFunction::PostEditChangeChainProperty(struct FPropertyChangedChainEvent& PropertyChangedEvent)
{
	Super::PostEditChangeChainProperty(PropertyChangedEvent);

	UpdateName();
}

void UBTT_ExecuteFunction::UpdateName()
{
	NodeName = FunctionContext.FunctionToExecute;
}
#endif
