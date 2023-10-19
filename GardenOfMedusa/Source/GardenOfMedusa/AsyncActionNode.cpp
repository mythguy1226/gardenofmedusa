// Fill out your copyright notice in the Description page of Project Settings.


#include "AsyncActionNode.h"

// Callable node usable in blueprints
UAsyncActionNode* UAsyncActionNode::MultiThreadedNode()
{
	// Return object as async action node
	UAsyncActionNode* Node = NewObject<UAsyncActionNode>();
	return Node;
}

// Activation
void UAsyncActionNode::Activate()
{
	// Creates a Non-abandonable task and starts it in the background
	(new FAutoDeleteAsyncTask<BP_NonAbandonableTask>(this))->StartBackgroundTask();
}

//**************************************************************

// Constructor used for setting the calling object
BP_NonAbandonableTask::BP_NonAbandonableTask(UAsyncActionNode* BP_TaskInstance)
{
	CallingObject = BP_TaskInstance;
}

// Destructor used for clean-up and broadcasting finished work
BP_NonAbandonableTask::~BP_NonAbandonableTask()
{
	CallingObject->FinishedWork.Broadcast();
	CallingObject->SetReadyToDestroy();
}

// Method called for broadcasting multi-threaded work
void BP_NonAbandonableTask::DoWork()
{
	CallingObject->MultiThreadedWork.Broadcast();
}
