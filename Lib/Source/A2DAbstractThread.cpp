
#include "../../Include/A2DExtLibs.h"
#include "../../Include/A2DAbstractThread.h"

A2DAbstractThread::A2DAbstractThread(A2DRunnable * xRunnable) : aRunnable (xRunnable) {}

A2DAbstractThread::~A2DAbstractThread(){}

HRESULT A2DAbstractThread::Initialize()
{
    if (aRunnable == NULL)
    {
        return E_FAIL;
    } 

    return S_OK;
}

void A2DAbstractThread::Deinitialize()
{
    if (isAlive())
    {
        stop();
    } 
}
