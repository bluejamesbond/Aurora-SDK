
#include "../../../Include/Windows/ExtLibs.h"
#include "../../../Include/Windows/Thread.h"

using namespace A2D;

Thread::Thread(Runnable * xRunnable) : AbstractThread(xRunnable), aThreadID (0) {}

Thread::~Thread()
{
	if (isAlive())
	{
		stop();
	}
}

bool Thread::start()
{
	aHThread = CreateThread(NULL, 0, &initThread, this, 0, &aThreadID);
	aHandles[AbstractThread::id()] = aHThread;
    return (aHThread != NULL);
}

void Thread::interrupt()
{
    SuspendThread(aHThread);
}

int Thread::id()
{
	return static_cast<int>(aThreadID);
}

void Thread::resume()
{
    int resumeCount = ResumeThread(aHThread);
  
    while (resumeCount > 1)
    {
        resumeCount = ResumeThread(aHThread);
    }
}

HANDLE Thread::aHandles[50];

void Thread::stop()
{
    if (aHThread)
    {
		TerminateThread( aHThread, 0 );
		CloseHandle(aHThread);
		aHandles[AbstractThread::id()] = NULL;
		aHThread= NULL;
    }
}

bool Thread::isAlive()
{
    return ((aHThread != NULL) && (WaitForSingleObject(aHThread, 0) != WAIT_OBJECT_0));
}

void Thread::waitAll()
{
	WaitForMultipleObjects(AbstractThread::getClassInstances(), aHandles, true, INFINITE);
}

int Thread::getCurrentThreadId()
{
	return static_cast<int>(GetCurrentThreadId());
}

DWORD WINAPI Thread::initThread(void * xParam)
{
	Thread * thread = reinterpret_cast<Thread*>(xParam);

	if (thread)
    {   
		thread->fire();

        return 0;
    }

    return -1;
}

LPCWSTR Thread::getClass()
{
	return L"Thread";
}

LPCWSTR Thread::toString()
{
	return L"Thread";
}