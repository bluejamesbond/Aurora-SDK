////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __ABSTRACTRHEAD_H__
#define __ABSTRACTRHEAD_H__

//+-----------------------------------------------------------------------------
//
//  Abstract Class:
//      ABSTRACTRHEAD
//
//  Synopsis:
//      Differentiates which of the two possible arcs could match the given arc
//      parameters.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////

#include "Abstract.h"
#include "Runnable.h"

////////////////////////////////////////////////////////////////////////////////
// DECLARATION
////////////////////////////////////////////////////////////////////////////////

class AbstractThread : public Abstract
{

public:

	AbstractThread(Runnable * xRunnable);
	~AbstractThread();

private:

	Runnable * aRunnable;

	int aId;
	static int aClassInstances;
	static AbstractThread * aClassInstance;

protected:

	void fire();
	static int getClassInstances();

public:

	static AbstractThread* getInstance();

	virtual int	 id();
	virtual bool start() = 0;
	virtual void interrupt() = 0;
	virtual void resume() = 0;
	virtual void stop() = 0;
	virtual bool isAlive() = 0;
	virtual void waitAll() = 0;
	virtual int getCurrentThreadId() = 0;

	////////////////////////////////////////////////////////////////////////////////
	// ABSTRACT
	////////////////////////////////////////////////////////////////////////////////

public:

	virtual HRESULT                 Initialize();
	virtual void                    Deinitialize();
	virtual LPCWSTR                 GetClass() = 0;
	virtual LPCWSTR                 ToString() = 0;
	virtual bool                    operator==(Abstract * xAbstract) = 0;

};

#endif