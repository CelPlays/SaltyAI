// Copyright 2019 - Now Salty Panda Studios. All Rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTT_ExecuteFunction.generated.h"

USTRUCT()
struct FFunctionContext
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TSubclassOf<UObject> ContextClass;

	UPROPERTY(EditAnywhere)
	FString FunctionToExecute;
};

UCLASS()
class SALTYAI_API UBTT_ExecuteFunction : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTT_ExecuteFunction() {};

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
	virtual void PostEditChangeChainProperty(struct FPropertyChangedChainEvent& PropertyChangedEvent) override;
	void UpdateName();
#endif

public:
	UPROPERTY(EditAnywhere)
	FFunctionContext FunctionContext;

	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector Target;

	UPROPERTY(EditAnywhere)
	bool bReturnSuccessIfInvalid = true;
};
