
#include "../../../include/Core/ExtLibs.h"
#include "../../../include/Core/Toolkit.h"
#include "../../../include/Core/AbstractEventQueue.h"

using namespace A2D;

int Toolkit::waitForBackgroundThreads()
{
	// DO null check here!
	return AbstractEventQueue::getInstance()->waitForAllDispatchingThreads();
}

AbstractEventQueue * Toolkit::aEventQueues[20];

int Toolkit::aEventQueuesIndex = -1;
int Toolkit::aEventQueuesLength = 20;

void Toolkit::addSystemEventQueue(AbstractEventQueue * xEventQueue)
{
	aEventQueues[++aEventQueuesIndex] = xEventQueue;
}

AbstractEventQueue* Toolkit::getSystemEventQueue(int xFrameInstanceIndex)
{
	return aEventQueues[xFrameInstanceIndex];
}