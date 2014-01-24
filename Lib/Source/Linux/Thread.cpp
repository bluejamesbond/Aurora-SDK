
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
}

int bugfixPThread() {
	return pthread_getconcurrency();
};

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
	aThreadHandles.push_back(&thread1, &aListHandle);

	// Increment parent activeCount
	AbstractThread::aActiveCount++;

    return true;
}

void Thread::interrupt()
{
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

}

bool Thread::isAlive()
{
	return false;
}

void Thread::waitAll()
{

}

int Thread::getCurrentThreadId()
{
	return 0;
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

