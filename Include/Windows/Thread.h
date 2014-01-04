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

#include "ExtLibs.h"
#include "../Abstract.h"
#include "../Runnable.h"
#include "../AbstractThread.h"
#include "../OrderedList.h"

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

	protected:

		static AbstractThread * aClassInstance;

	private:

		static DWORD WINAPI initThread(void * xParam);

		////////////////////////////////////////////////////////////////////////////////
		// ABSTRACT
		////////////////////////////////////////////////////////////////////////////////

	public:

		virtual LPCWSTR                 getClass();
		virtual LPCWSTR                 toString();

	};
}
#endif