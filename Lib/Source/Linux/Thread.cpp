
#include "../../../Include/Linux/ExtLibs.h"
#include "../../../Include/Linux/Thread.h"

using namespace A2D;

// Set an instance of this. So it can call waitAll
AbstractThread* Thread::aClassInstance = new Thread(NULL); 

// Intiialize the OrderedList
OrderedList<pthread_t*> Thread::aThreadHandles;

Thread::Thread(Runnable * xRunnable) : AbstractThread(xRunnable)
{
	// Default thread id is 0 until we get
	// an actual thread id from kernel
	aId = 0;

	// Bug fix for Ubunto 13.10
	pthread_getconcurrency();
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
}

bool Thread::start()
{
    //
    return true;
}

bool Thread::start(void * (*start_routine)(void *), void* arg)
{ 
	int policy;
	struct sched_param param;

	// Get thread via kernel level request
    int result = pthread_create( &thread1, NULL, Thread::initThread, static_cast<void*>(this));

	// Set priority just because we can
    pthread_getschedparam(thread1, &policy, &param);
    param.sched_priority = sched_get_priority_max(policy);
    pthread_setschedparam(thread1, policy, &param);

	// Get the handle from OrderedList and store it
	aThreadHandles.push_back(&thread1, &m_threadHandle);

	// Increment parent activeCount
	AbstractThread::aActiveCount++;

    return true;
}

void Thread::interrupt()
{
	// FIXME Study how to interrupt thread and
	// add the code for that
}

int Thread::id()
{
	//return an integer format of thread id
	return INT(aId);
}

void Thread::resume()
{

}

void Thread::stop()
{
	// FIXME Study how to stop thread and
	// add the code for that

	// Get the handle from OrderedList and store it
	aThreadHandles.remove_request(&m_threadHandle);

	// Decrement parent activeCount
	AbstractThread::aActiveCount--;
}

bool Thread::isAlive()
{
	return false;
}

void Thread::waitAll()
{
	pthread_t ** allActiveThreads = aThreadHandles.to_array();
	int size = aThreadHandles.size();

	// Force all the threads to join
	for(int i = 0; i < size; i++)
	{
		pthread_join(*allActiveThreads[i], NULL);
	}

}

int Thread::getCurrentThreadId()
{
	return static_cast<int>(getpid());
}

void* Thread::initThread(void * xParam)
{
	Thread * thread = reinterpret_cast<Thread*>(xParam);

	// If thread exists
	if (thread)
    {   
		// Fire the thread which is defined in 
		// super class : AbstracThread
		thread->fire();

        return NULL;
    }

    return NULL;
}

