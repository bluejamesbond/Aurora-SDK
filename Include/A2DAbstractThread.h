////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __A2DABSTRACTRHEAD_H__
#define __A2DABSTRACTRHEAD_H__

//+-----------------------------------------------------------------------------
//
//  Abstract Class:
//      A2DABSTRACTRHEAD
//
//  Synopsis:
//      Differentiates which of the two possible arcs could match the given arc
//      parameters.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////

#include "A2DAbstract.h"
#include "A2DRunnable.h"

////////////////////////////////////////////////////////////////////////////////
// DECLARATION
////////////////////////////////////////////////////////////////////////////////

class A2DAbstractThread : public A2DAbstract
{

public:

	A2DAbstractThread(A2DRunnable * xRunnable);
	~A2DAbstractThread();

private:

	A2DRunnable * aRunnable;

	int aId;
	static int aClassInstances;
	static A2DAbstractThread * aClassInstance;

protected:

	void fire();
	static int getClassInstances();

public:

	static A2DAbstractThread* getInstance();

	virtual int	 id();
	virtual bool start() = 0;
	virtual void interrupt() = 0;
	virtual void resume() = 0;
	virtual void stop() = 0;
	virtual bool isAlive() = 0;
	virtual void waitAll() = 0;
	virtual int getCurrentThreadId() = 0;

	////////////////////////////////////////////////////////////////////////////////
	// A2DABSTRACT
	////////////////////////////////////////////////////////////////////////////////

public:

	virtual HRESULT                 Initialize();
	virtual void                    Deinitialize();
	virtual LPCWSTR                 GetClass() = 0;
	virtual LPCWSTR                 ToString() = 0;
	virtual bool                    operator==(A2DAbstract * xAbstract) = 0;

};

#endif