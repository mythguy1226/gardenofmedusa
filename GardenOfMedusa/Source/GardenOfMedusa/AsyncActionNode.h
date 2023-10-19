// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "AsyncActionNode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTaskOutput);

/**
 * 
 */
UCLASS()
class GARDENOFMEDUSA_API UAsyncActionNode : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()
	
public:
	// Function calls for both multi-threaded work and when that work is finished
	UPROPERTY(BlueprintAssignable)
	FTaskOutput MultiThreadedWork;

	UPROPERTY(BlueprintAssignable)
	FTaskOutput FinishedWork;

	// Callable blueprint node
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))
	static UAsyncActionNode* MultiThreadedNode();

	// Method called upon activation
	virtual void Activate() override;
};

//****************************************************************************************

class BP_NonAbandonableTask : public FNonAbandonableTask
{
public:
	// Constructor/Destructor
	BP_NonAbandonableTask(UAsyncActionNode* BP_TaskInstance);

	~BP_NonAbandonableTask();

	// Needed for UE5
	FORCEINLINE TStatId GetStatId() const
	{
		RETURN_QUICK_DECLARE_CYCLE_STAT(BP_NonAbandonableTask, STATGROUP_ThreadPoolAsyncTasks);
	}

	// Object to run work on
	UAsyncActionNode* CallingObject = nullptr;

	// Method for running multi-threaded work
	void DoWork();
};
