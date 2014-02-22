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

		Thread(Runnable * xRunnable, void * x_param);
		virtual ~Thread();

	private:

		HANDLE aHThread;
		DWORD aId;

		void * aListHandle;
		static OrderedList<HANDLE> aThreadHandles;

	public:

		virtual bool start();
		virtual void interrupt();
		virtual void resume();
		virtual void stop();
		virtual bool isAlive();
		virtual int	id();
		virtual void waitAll();
		virtual int getCurrentThreadId();
		
	private:

		static DWORD WINAPI initThread(void * xParam);
		
	};
}
#endif