
#include "../../../Include/Windows/ExtLibs.h"
#include "../../../Include/Windows/Thread.h"

using namespace A2D;

// Intiialize the OrderedList
OrderedList<HANDLE> Thread::aThreadHandles;

Thread::Thread(Runnable * xRunnable) : AbstractThread(xRunnable)
{
	// Default thread id is 0 until we get
	// an actual thread id from kernel
	aId = 0;
}

Thread::~Thread()
{
	// Obviously check if it is alive then stop
	// Due to limitations in C++ code, we can't 
	// do this in AbstractThread. But you should
	// do this in all children classes of AbstractThread
	if (isAlive())
	{
		stop();
	}

	// Call super deconstructor
	AbstractThread::~AbstractThread();
}

bool Thread::start()
{ 
	// Get thread via kernel level request
	aHThread = CreateThread(NULL, 0, &initThread, this, 0, &aId);

	// Set priority just because we can
	SetThreadPriority(aHThread, THREAD_PRIORITY_TIME_CRITICAL);

	// Get the handle from OrderedList and store it
	aThreadHandles.push_back(aHThread, &aListHandle);

	// Increment parent activeCount
	AbstractThread::aActiveCount++;

    return (aHThread != NULL);
}

void Thread::interrupt()
{
	// Check if thread exists
	if (aHThread)
	{
		SuspendThread(aHThread);

		// Decrement parent activeCount
		AbstractThread::aActiveCount--; 
	}
}

int Thread::id()
{
	//return an integer format of thread id
	return SINT(aId);
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

		// Increment parent activeCount
		AbstractThread::aActiveCount++; 
	}
}

void Thread::stop()
{
    if (aHThread)
    {
		TerminateThread( aHThread, 0 );
		CloseHandle(aHThread);
		aHThread = NULL;

		// Request remove of the list handle
		aThreadHandles.remove_request(&aListHandle);
		
		// Decrement parent activeCount
		AbstractThread::aActiveCount--;
    }
}

bool Thread::isAlive()
{
	// Kernel level waiting to see if thread is still alive.
	// If it is alive, and the wait time is 0, then we know
	// that the WAIT has not been signaled (WAIT_OBJECT_0)
	// Another way to setting the wait time to something really
	// small like 1ms and then see if the signal has not been fired
	// i.e. WaitForSingleObject(aHThread, 0) == WAIT_TIMEOUT
    return ((aHThread != NULL) && (WaitForSingleObject(aHThread, 0) != WAIT_OBJECT_0));
}

void Thread::waitAll()
{
	// Use the kernel wait for every thread that has been created.
	WaitForMultipleObjects(aThreadHandles.size(), aThreadHandles.to_array(), true, INFINITE);
}

int Thread::getCurrentThreadId()
{
	// returns the current thread from the kernel level
	return SINT(GetCurrentThreadId());
}

// This static method is used as the logic loop behind
// thread creation and starting every thread. Different
// platforms have different techniques, Windows just happens
// to do it this way.
DWORD WINAPI Thread::initThread(void * xParam)
{
	Thread * thread = reinterpret_cast<Thread*>(xParam);

	// If thread exists
	if (thread)
    {   
		// Fire the thread which is defined in 
		// super class : AbstracThread
		thread->fire();

        return 0;
    }

    return -1;
}