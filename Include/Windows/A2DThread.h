////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __A2DTHREAD_H__
#define __A2DTHREAD_H__

//+-----------------------------------------------------------------------------
//
//  Abstract Class:
//      A2DTHREAD
//
//  Synopsis:
//      Differentiates which of the two possible arcs could match the given arc
//      parameters.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////

#include "A2DExtLibs.h"
#include "../A2DAbstract.h"
#include "../A2DRunnable.h"
#include "../A2DAbstractThread.h"

////////////////////////////////////////////////////////////////////////////////
// DECLARATION
////////////////////////////////////////////////////////////////////////////////

using namespace std;

class A2DThread : public A2DAbstractThread
{

public:

	A2DThread(A2DRunnable * xRunnable);
	~A2DThread();

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
// A2DABSTRACT
////////////////////////////////////////////////////////////////////////////////

public:

	virtual LPCWSTR                 GetClass();
	virtual LPCWSTR                 ToString();
	virtual bool                    operator==(A2DAbstract * xAbstract);

};

#endif