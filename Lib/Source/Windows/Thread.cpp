
#include "../../../Include/Windows/ExtLibs.h"
#include "../../../Include/Windows/Thread.h"

using namespace A2D;

AbstractThread* Thread::aClassInstance = new Thread(NULL); // Set an instance of this. So it can call waitAll

Thread::Thread(Runnable * xRunnable) : AbstractThread(xRunnable)
{
	aThreadID = 0;
}

Thread::~Thread()
{
	if (isAlive())
	{
		stop();
	}

	AbstractThread::~AbstractThread(); // Call super deconstructor
}


bool Thread::start()
{
	AbstractThread::aActiveCount++; // Increment parent activeCount

	aHThread = CreateThread(NULL, 0, &initThread, this, 0, &aThreadID);
	SetThreadPriority(aHThread, THREAD_PRIORITY_TIME_CRITICAL);
	aHandles[AbstractThread::id()] = aHThread;

    return (aHThread != NULL);
}

void Thread::interrupt()
{
	if (aHThread)
	{
		SuspendThread(aHThread);
		AbstractThread::aActiveCount--; // Decrement parent activeCount
	}
}

int Thread::id()
{
	return static_cast<int>(aThreadID);
}

void Thread::resume()
{
	if (aHThread)
	{
		int resumeCount = ResumeThread(aHThread);
		
		while (resumeCount > 1)
		{
			resumeCount = ResumeThread(aHThread);
		}

		AbstractThread::aActiveCount++; // Increment parent activeCount
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
		aHThread = NULL;
		AbstractThread::aActiveCount--; // Decrement parent activeCount
    }
}

bool Thread::isAlive()
{
    return ((aHThread != NULL) && (WaitForSingleObject(aHThread, 0) != WAIT_OBJECT_0));
}

void Thread::waitAll()
{
	WaitForMultipleObjects(AbstractThread::instanceCount(), aHandles, true, INFINITE);
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