// Copyright 2019 - Now Salty Panda Studios. All Rights reserved.

#include "BTComposite_Sequenceloop.h"

UBTComposite_SequenceLoop::UBTComposite_SequenceLoop(const FObjectInitializer& Initializer)
	:Super(Initializer)
{
	bUseNodeActivationNotify = true;
}

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
		else if(CurrentLoopCount < ActiveLoopCount)
		{
			CurrentLoopCount++;
			NextChildIdx = 0;
		}
	}

	return NextChildIdx;
}

void UBTComposite_SequenceLoop::NotifyNodeActivation(FBehaviorTreeSearchData& SearchData) const
{
	CurrentLoopCount = 1;

	const int32 MinNum = FMath::Max(0, LoopCount - LoopDeviation);
	const int32 MaxNum = FMath::Max(0, LoopCount + LoopDeviation);

	ActiveLoopCount = FMath::RandRange(MinNum, MaxNum);
}

#if WITH_EDITOR

void UBTComposite_SequenceLoop::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if (LoopDeviation == 0)
	{
		NodeName = FString::Printf(TEXT("Sequence runs %d times"), LoopCount);
	}
	else
	{
		const int32 MinNum = FMath::Max(0, LoopCount - LoopDeviation);
		const int32 MaxNum = FMath::Max(0, LoopCount + LoopDeviation);

		NodeName = FString::Printf(TEXT("Sequence runs between %d and %d times"), MinNum, MaxNum);
	}
}

#endif