// Copyright 2019 - Now Salty Panda Studios. All Rights reserved.

#include "BTComposite_SelectRandom.h"

UBTComposite_SelectRandom::UBTComposite_SelectRandom(const FObjectInitializer& Initializer)
	:Super(Initializer)
{
	bUseNodeActivationNotify = true;
	NodeName = "Select Random";
}

int32 UBTComposite_SelectRandom::GetNextChildHandler(struct FBehaviorTreeSearchData& SearchData, int32 PrevChild, EBTNodeResult::Type LastResult) const
{
	if(!bAlreadyRan)
	{
		bAlreadyRan = true;
		int32 Child = FMath::RandRange(0, GetChildrenNum() - 1);
		return Child;
	}

	return BTSpecialChild::ReturnToParent;
}

void UBTComposite_SelectRandom::NotifyNodeActivation(FBehaviorTreeSearchData& SearchData) const
{
	bAlreadyRan = false;
}
