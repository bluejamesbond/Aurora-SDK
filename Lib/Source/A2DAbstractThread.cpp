
#include "../../Include/A2DExtLibs.h"
#include "../../Include/A2DAbstractThread.h"

A2DAbstractThread::A2DAbstractThread(A2DRunnable * xRunnable) : aRunnable (xRunnable) {}

A2DAbstractThread::~A2DAbstractThread(){}

void A2DAbstractThread::fire()
{
	if (aRunnable)
	{
		aRunnable->run(id());
	}
}

int A2DAbstractThread::aClassInstances = -1;

A2DAbstractThread* A2DAbstractThread::aClassInstance = NULL;

int A2DAbstractThread::getClassInstances()
{
	return aClassInstances + 1;
}

A2DAbstractThread& A2DAbstractThread::getInstance()
{
	return *aClassInstance;
}

HRESULT A2DAbstractThread::Initialize()
{
    if (aRunnable == NULL)
    {
        return E_FAIL;
    } 

	aClassInstance = this;

	aId = ++aClassInstances;
	
    return S_OK;
}

int A2DAbstractThread::id()
{
	return aId;
}

void A2DAbstractThread::Deinitialize()
{
    if (isAlive())
    {
        stop();
    } 
}
