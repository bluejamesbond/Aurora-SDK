
#include "../../../Include/Core/ExtLibs.h"
#include "../../../Include/Core/AbstractThread.h"

using namespace A2D;

int AbstractThread::aInstanceCount = -1;
int AbstractThread::aActiveCount = 0;

AbstractThread* AbstractThread::aSingleton = NULL;

AbstractThread::AbstractThread(Runnable * xRunnable, void * x_param) :
	m_param(x_param),
	aRunnable(xRunnable)
{
}

AbstractThread::~AbstractThread()
{
	aInstanceCount--;
}

void AbstractThread::fire()
{
	if (aRunnable)
	{
		aRunnable->run(m_param, id());
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

STATUS AbstractThread::initialize()
{

	NULLCHECK(aRunnable);

	aSingleton = this;

	aId = ++aInstanceCount;

	return STATUS_OK;
}

int AbstractThread::id()
{
	return aId;
}