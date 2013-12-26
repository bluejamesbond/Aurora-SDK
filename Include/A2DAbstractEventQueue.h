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
#include "A2DRunnable.h"
#include "A2DRect.h"

////////////////////////////////////////////////////////////////////////////////
// FORWARD DECLARATIONS
////////////////////////////////////////////////////////////////////////////////

class A2DAbstractWindow;
class A2DWindow;

////////////////////////////////////////////////////////////////////////////////
// DECLARATION
////////////////////////////////////////////////////////////////////////////////


class A2DAbstractEventQueue : public A2DRunnable, public A2DAbstract
{
public:

    // Constructor
    A2DAbstractEventQueue(A2DAbstractWindow * xWindow);

    // Deconstructor
    ~A2DAbstractEventQueue();

private:

    A2DRunnable               *     aImmediateRunnable;

protected:

    A2DAbstractWindow         *     aWindow;

public:

    void                            invokeLater(A2DRunnable * xRunnable);
    void                            invokeAndWait(A2DRunnable * xRunnable);
    void                            clearQueue();

    bool							isDispatchingThread();
    void							invokeRerender();
    void							invokeRevalidate();
    void							invokeReset();

    void                            invokeAnimationFrame(int xTime, A2DRunnable * xRunnable);
	
protected:

    // Queue
    virtual bool                    getQueueLock() = 0;
	virtual void                    releaseQueueLock() = 0;
	virtual A2DRunnable *           peekEvent() = 0;
	virtual void					popEvent() = 0;
    virtual void                    pushEvent(A2DRunnable * xRunnable) = 0;
	virtual bool                    hasEvent() = 0;
	virtual void                    removeAllEvents() = 0;
	virtual void					run() = 0;

public:

    // Thread
    virtual void                    startDispatchingThread() = 0;
    virtual void                    suspendDispatchingThread() = 0;
    virtual void                    resumeDispatchingThread() = 0;

////////////////////////////////////////////////////////////////////////////////
// A2DABSTRACT
////////////////////////////////////////////////////////////////////////////////

public:

	virtual HRESULT                 Initialize();
	virtual void                    Deinitialize() = 0;
	virtual LPCWSTR                 GetClass() = 0;
	virtual LPCWSTR                 ToString() = 0;
	virtual bool                    operator==(A2DAbstract * xAbstract) = 0;

};

#endif
