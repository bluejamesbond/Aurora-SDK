
#include "../../include/A2DExtLibs.h"
#include "../../include/A2DToolkit.h"
#include "../../include/A2DAbstractEventQueue.h"

int A2DToolkit::waitForUI()
{
	return A2DAbstractEventQueue::getInstance().waitForAllDispatchingThreads();
}