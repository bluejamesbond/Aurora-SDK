////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __A2DEVENTQUEUE_H__
#define __A2DEVENTQUEUE_H__

//+-----------------------------------------------------------------------------
//
//  Class:
//      A2DWINDOW
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
#include "A2DThread.h"
#include "A2DWindow.h"
#include "../A2DRunnable.h"
#include "../A2DAbstract.h"
#include "../A2DAbstractEventQueue.h"

////////////////////////////////////////////////////////////////////////////////
// FORWARD DECLARATIONS
////////////////////////////////////////////////////////////////////////////////

class A2DFrame;
class A2DAbstract;
class A2DThread;

////////////////////////////////////////////////////////////////////////////////
// DECLARATION
////////////////////////////////////////////////////////////////////////////////

using namespace std;

class A2DEventQueue : public A2DAbstractEventQueue
{
public:

	A2DEventQueue::A2DEventQueue(A2DAbstractWindow * xWindow);

	A2DEventQueue::~A2DEventQueue();

private:

	queue<A2DRunnable*> * aEventQueue;
	HANDLE aEventQueueLock;
	A2DThread * aThread;

protected:
	
	// Queue
	virtual bool                    getQueueLock();
	virtual void                    releaseQueueLock();
	virtual A2DRunnable *           peekEvent();
	virtual void					popEvent();
	virtual void                    pushEvent(A2DRunnable * xRunnable);
	virtual bool                    hasEvent();
	virtual void                    removeAllEvents();
	virtual void					run(); // Acts as message loop!

public:

	// Thread - Move from OS level to Global level!!!
	virtual void                    startDispatchingThread();
	virtual void                    suspendDispatchingThread();
	virtual void                    resumeDispatchingThread();



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