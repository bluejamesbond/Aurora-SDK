////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __THREAD_H__
#define __THREAD_H__

//+-----------------------------------------------------------------------------
//
//  Abstract Class:
//      THREAD
//
//  Synopsis:
//      Differentiates which of the two possible arcs could match the given arc
//      parameters.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////

#include "../Core/Runnable.h"
#include "../Core/AbstractThread.h"
#include "../Core/OrderedList.h"

#include "ExtLibs.h"

using namespace std;

namespace A2D {

	////////////////////////////////////////////////////////////////////////////////
	// DECLARATION
	////////////////////////////////////////////////////////////////////////////////

	class Thread : public AbstractThread
	{

	public:

		Thread(Runnable * xRunnable);
		virtual ~Thread();

	private:
        pthread_t thread1;
        int retval;

		void * aListHandle;
		static OrderedList<pthread_t*> aThreadHandles;

	public:

		virtual bool start();
        virtual bool start(void * (*start_routine)(void *), void* arg);
		virtual void interrupt();
		virtual void resume();
		virtual void stop();
		virtual bool isAlive();
        virtual int	 id();
		virtual void waitAll();
        virtual int  getCurrentThreadId();

	protected:

		static AbstractThread * aClassInstance;

	private:

		static void* initThread(void * xParam);

	};
}
#endif
