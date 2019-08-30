// Copyright 2019 - Now Salty Panda Studios. All Rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTCompositeNode.h"
#include "BTComposite_SelectRandom.generated.h"

UCLASS()
class SALTYAI_API UBTComposite_SelectRandom : public UBTCompositeNode
{
	GENERATED_BODY()

public:
	UBTComposite_SelectRandom(const FObjectInitializer& Initializer);

protected:
	virtual int32 GetNextChildHandler(struct FBehaviorTreeSearchData& SearchData, int32 PrevChild, EBTNodeResult::Type LastResult) const override;
	virtual void NotifyNodeActivation(FBehaviorTreeSearchData& SearchData) const;

public:
	UPROPERTY()
	mutable bool bAlreadyRan = false;
};
