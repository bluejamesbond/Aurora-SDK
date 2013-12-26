////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __A2DABSTRACTEVENTQUEUE_H__
#define __A2DABSTRACTEVENTQUEUE_H__

//+-----------------------------------------------------------------------------
//
//  Abstract Class:
//      A2DABSTRACTEVENTQUEUE
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
#include "A2DRenderable.h"
#include "A2DAbstractThread.h"
#include "A2DToolkit.h"
#include "A2DRunnable.h"
#include "A2DRect.h"

////////////////////////////////////////////////////////////////////////////////
// FORWARD DECLARATIONS
////////////////////////////////////////////////////////////////////////////////

class A2DAbstractFrame;
class A2DAbstractWindow;
class A2DWindow;

////////////////////////////////////////////////////////////////////////////////
// DECLARATION
////////////////////////////////////////////////////////////////////////////////


class A2DAbstractEventQueue : public A2DRunnable, public A2DAbstract
{
public:

	A2DAbstractEventQueue(A2DAbstractFrame * xFrame);

private:

    A2DRunnable               *     aImmediateRunnable = NULL;
	A2DAbstractThread		  *		aThread = NULL;

protected:

    A2DAbstractWindow         *     aWindow;
	A2DAbstractFrame		  *		aFrame;

public:

    void                            invokeLater(A2DRunnable * xRunnable);
    void                            invokeAndWait(A2DRunnable * xRunnable);
    void                            clearQueue();

    bool							isDispatchingThread();
    void							invokeRerender();
    void							invokeRevalidate();
    void							invokeReset();

    void                            invokeAnimationFrame(int xTime, A2DRunnable * xRunnable);
	
	int		 						waitForAllDispatchingThreads();

	void							startDispatchingThread();
	void							suspendDispatchingThread();
	void							resumeDispatchingThread();

	static A2DAbstractEventQueue*	aInstance;
	static A2DAbstractEventQueue&	getInstance();

protected:

    // Queue
    virtual bool                    getQueueLock() = 0;
	virtual void                    releaseQueueLock() = 0;
	virtual A2DRunnable *           peekEvent() = 0;
	virtual void					popEvent() = 0;
    virtual void                    pushEvent(A2DRunnable * xRunnable) = 0;
	virtual bool                    hasEvent() = 0;
	virtual void                    removeAllEvents() = 0;
	virtual void					run(); // Message loop goes in here; Hard coded!

	// Creators
	virtual A2DAbstractThread*		createPlatformCompatibleThread(A2DRunnable * xRunnable) = 0;

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
