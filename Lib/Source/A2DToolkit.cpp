
#include "../../include/A2DExtLibs.h"
#include "../../include/A2DToolkit.h"
#include "../../include/A2DAbstractEventQueue.h"

int A2DToolkit::waitForBackgroundThreads()
{
	// DO null check here!
	return A2DAbstractEventQueue::getInstance()->waitForAllDispatchingThreads();
}

A2DAbstractEventQueue * A2DToolkit::aEventQueues[20];

int A2DToolkit::aEventQueuesIndex = -1;
int A2DToolkit::aEventQueuesLength = 20;

void A2DToolkit::addSystemEventQueue(A2DAbstractEventQueue * xEventQueue)
{
	aEventQueues[++aEventQueuesIndex] = xEventQueue;
}

A2DAbstractEventQueue* A2DToolkit::getSystemEventQueue(int xFrameInstanceIndex)
{
	return aEventQueues[xFrameInstanceIndex];
}