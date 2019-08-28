// Copyright 2019 - Now Salty Panda Studios. All Rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTT_SetBlackboardProperty.generated.h"

USTRUCT()
struct FBlackboardKeyChanger
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FString StringValue;

	UPROPERTY(EditAnywhere)
	int32 IntValue;

	UPROPERTY(EditAnywhere)
	float FloatValue;

	UPROPERTY(EditAnywhere)
	bool BoolValue;

	UPROPERTY(EditAnywhere)
	FName NameValue;

	UPROPERTY(EditAnywhere)
	uint8 EnumValue;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UObject> ClassValue;
};

DECLARE_DELEGATE(FTaskChanged);

UCLASS()
class SALTYAI_API UBTT_SetBlackboardProperty : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTT_SetBlackboardProperty() {};

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
	virtual void PostEditChangeChainProperty(struct FPropertyChangedChainEvent& PropertyChangedEvent) override;
	void UpdateName();
#endif

public:
	FTaskChanged OnChanged;

	UPROPERTY(EditAnywhere)
		FBlackboardKeyChanger BlackboardValue;

	UPROPERTY(EditAnywhere)
		FBlackboardKeySelector Key;

	UPROPERTY(EditAnywhere)
		bool bReturnSuccessIfInvalid = true;
};
