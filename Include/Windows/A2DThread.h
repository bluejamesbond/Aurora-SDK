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

#include "../A2DAbstract.h"
#include "../A2DRunnable.h"

////////////////////////////////////////////////////////////////////////////////
// DECLARATION
////////////////////////////////////////////////////////////////////////////////

class A2DThread : public A2DAbstract
{

public:

	A2DThread(A2DRunnable * xRunnable);
	~A2DThread();

private:

	A2DRunnable * aRunnable;
	HANDLE aHThread;
	DWORD aThreadID;

public:

	bool start();
	void interrupt();
	void resume();
	void stop();
	bool isAlive();
	int	id();

protected:

	void				fire();
	static DWORD WINAPI initThread(void * xParam);

////////////////////////////////////////////////////////////////////////////////
// A2DABSTRACT
////////////////////////////////////////////////////////////////////////////////

public:

	virtual HRESULT                 Initialize();
	virtual void                    Deinitialize();
	virtual LPCWSTR                 GetClass();
	virtual LPCWSTR                 ToString();
	virtual bool                    operator==(A2DAbstract * xAbstract);

};

#endif