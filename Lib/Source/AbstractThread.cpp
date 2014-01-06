
#include "../../Include/ExtLibs.h"
#include "../../Include/AbstractThread.h"

using namespace A2D;

int AbstractThread::aInstanceCount = -1;
int AbstractThread::aActiveCount = 0;

AbstractThread* AbstractThread::aSingleton = NULL;

AbstractThread::AbstractThread(Runnable * xRunnable)
{
	aRunnable = xRunnable;
}

AbstractThread::~AbstractThread()
{
	aInstanceCount--;
}


void AbstractThread::fire()
{
	if (aRunnable)
	{
		aRunnable->run(id());
	}
}

int AbstractThread::activeCount()
{
	return aActiveCount;
}

int AbstractThread::instanceCount()
{
	return aInstanceCount + 1;
}


AbstractThread* AbstractThread::getSingleton()
{
	return aSingleton;
}

HRESULT AbstractThread::initialize()
{
	NULLCHECK(aRunnable);

	aId = ++aInstanceCount;

	return S_OK;
}

int AbstractThread::id()
{
	return aId;
}