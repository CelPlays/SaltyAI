// Copyright 2019 - Now Salty Panda Studios. All Rights reserved.

#include "BTComposite_Sequenceloop.h"

int32 UBTComposite_SequenceLoop::GetNextChildHandler(struct FBehaviorTreeSearchData& SearchData, int32 PrevChild, EBTNodeResult::Type LastResult) const
{
	// failure = quit
	int32 NextChildIdx = BTSpecialChild::ReturnToParent;

	if (PrevChild == BTSpecialChild::NotInitialized)
	{
		// newly activated: start from first
		NextChildIdx = 0;
	}
	else if (LastResult == EBTNodeResult::Succeeded)
	{
		if ((PrevChild + 1) < GetChildrenNum())
		{
			// success = choose next child
			NextChildIdx = PrevChild + 1;
		}
		//Otherwise check if we reached max loops
		else if(CurrentLoopCount < LoopCount)
		{
			CurrentLoopCount++;
			NextChildIdx = 0;
		}
	}

	if (NextChildIdx == BTSpecialChild::ReturnToParent)
	{
		CurrentLoopCount = 1;
	}

	return NextChildIdx;
}

#if WITH_EDITOR

void UBTComposite_SequenceLoop::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	NodeName = FString::Printf(TEXT("Sequence runs %d times"), LoopCount);
}

#endif