
#include "../../Include/ExtLibs.h"
#include "../../Include/AbstractThread.h"

using namespace A2D;

AbstractThread::AbstractThread(Runnable * xRunnable) : aRunnable (xRunnable) {}

AbstractThread::~AbstractThread(){}

void AbstractThread::fire()
{
	if (aRunnable)
	{
		aRunnable->run(id());
	}
}

int AbstractThread::aClassInstances = -1;

AbstractThread* AbstractThread::aClassInstance = NULL;

int AbstractThread::getClassInstances()
{
	return aClassInstances + 1;
}

AbstractThread* AbstractThread::getInstance()
{
	return aClassInstance;
}

HRESULT AbstractThread::initialize()
{
    if (aRunnable == NULL)
    {
        return E_FAIL;
    } 

	aClassInstance = this;

	aId = ++aClassInstances;
	
    return S_OK;
}

int AbstractThread::id()
{
	return aId;
}

void AbstractThread::Deinitialize()
{
    if (isAlive())
    {
        stop();
    } 
}
