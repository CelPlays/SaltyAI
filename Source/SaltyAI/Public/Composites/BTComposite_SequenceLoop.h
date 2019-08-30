// Copyright 2019 - Now Salty Panda Studios. All Rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Composites/BTComposite_Sequence.h"
#include "BTComposite_SequenceLoop.generated.h"

UCLASS()
class SALTYAI_API UBTComposite_SequenceLoop : public UBTComposite_Sequence
{
	GENERATED_BODY()

public:
#if WITH_EDITOR
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

protected:
	virtual int32 GetNextChildHandler(struct FBehaviorTreeSearchData& SearchData, int32 PrevChild, EBTNodeResult::Type LastResult) const override;

public:
	UPROPERTY(EditAnywhere, meta = (ClampMin = "1", ClampMax = "100", UIMin = "1", UIMax = "100"))
	int32 LoopCount = 1;

	UPROPERTY()
	mutable int32 CurrentLoopCount = 1;
};
