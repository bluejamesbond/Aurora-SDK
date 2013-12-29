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

////////////////////////////////////////////////////////////////////////////////
// DECLARATION
////////////////////////////////////////////////////////////////////////////////

using namespace std;

class Thread : public AbstractThread
{

public:

	Thread(Runnable * xRunnable);
	~Thread();

private:
	
	HANDLE aHThread;
	DWORD aThreadID;

	static HANDLE aHandles[50];

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

	static DWORD WINAPI initThread(void * xParam);

////////////////////////////////////////////////////////////////////////////////
// ABSTRACT
////////////////////////////////////////////////////////////////////////////////

public:

	virtual LPCWSTR                 GetClass();
	virtual LPCWSTR                 ToString();
	virtual bool                    operator==(Abstract * xAbstract);

};

#endif