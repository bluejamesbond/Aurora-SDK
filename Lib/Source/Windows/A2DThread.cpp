
#include "../../../Include/Windows/A2DExtLibs.h"
#include "../../../Include/Windows/A2DThread.h"

A2DThread::A2DThread(A2DRunnable * xRunnable) : A2DAbstractThread(xRunnable), aThreadID (0) {}

A2DThread::~A2DThread(){}

bool A2DThread::start()
{
	aHThread = CreateThread(NULL, 0, &initThread, this, 0, &aThreadID);
	aHandles[A2DAbstractThread::id()] = aHThread;
    return (aHThread != NULL);
}

void A2DThread::interrupt()
{
    SuspendThread(aHThread);
}

int A2DThread::id()
{
	return static_cast<int>(aThreadID);
}

void A2DThread::resume()
{
    int resumeCount = ResumeThread(aHThread);
  
    while (resumeCount > 1)
    {
        resumeCount = ResumeThread(aHThread);
    }
}

HANDLE A2DThread::aHandles[50];

void A2DThread::stop()
{
    if (aHThread)
    {
		TerminateThread( aHThread, 0 );
		CloseHandle(aHThread);
		aHandles[A2DAbstractThread::id()] = NULL;
		aHThread= NULL;
    }
}

bool A2DThread::isAlive()
{
    return ((aHThread != NULL) && (WaitForSingleObject(aHThread, 0) != WAIT_OBJECT_0));
}

void A2DThread::waitAll()
{
	WaitForMultipleObjects(A2DAbstractThread::getClassInstances(), aHandles, true, INFINITE);
}

int A2DThread::getCurrentThreadId()
{
	return static_cast<int>(GetCurrentThreadId());
}

DWORD WINAPI A2DThread::initThread(void * xParam)
{
	A2DThread * thread = reinterpret_cast<A2DThread*>(xParam);

	if (thread)
    {   
		thread->fire();

        return 0;
    }

    return -1;
}

LPCWSTR A2DThread::GetClass()
{
	return L"A2DThread";
}

LPCWSTR A2DThread::ToString()
{
	return L"A2DThread";
}

bool A2DThread::operator==(A2DAbstract * xAbstract)
{
	return false;
}