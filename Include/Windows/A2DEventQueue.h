////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __EVENTQUEUE_H__
#define __EVENTQUEUE_H__

//+-----------------------------------------------------------------------------
//
//  Class:
//      WINDOW
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
#include "Thread.h"
#include "Window.h"
#include "../Runnable.h"
#include "../Abstract.h"
#include "../AbstractEventQueue.h"

////////////////////////////////////////////////////////////////////////////////
// FORWARD DECLARATIONS
////////////////////////////////////////////////////////////////////////////////

class Frame;
class Abstract;
class Thread;

////////////////////////////////////////////////////////////////////////////////
// DECLARATION
////////////////////////////////////////////////////////////////////////////////

using namespace std;

class EventQueue : public AbstractEventQueue
{
public:

	EventQueue::EventQueue(AbstractFrame * xFrame);

	EventQueue::~EventQueue();

private:

	queue<Runnable*> * aEventQueue;
	HANDLE aEventQueueLock;
	HINSTANCE aHIsntance;

public:
	
	// Queue
	virtual bool                    getQueueLock();
	virtual void                    releaseQueueLock();
	virtual Runnable *           peekEvent();
	virtual void					popEvent();
	virtual bool                    hasEvent();

protected:

	virtual void                    pushEvent(Runnable * xRunnable);
	virtual void                    removeAllEvents();

public:

	// Thread - Move from OS level to Global level!!!
	virtual AbstractThread *		createPlatformCompatibleThread(Runnable * xRunnable);



////////////////////////////////////////////////////////////////////////////////
// ABSTRACT
////////////////////////////////////////////////////////////////////////////////

public:

	virtual HRESULT                 Initialize();
	virtual void                    Deinitialize();
	virtual LPCWSTR                 GetClass();
	virtual LPCWSTR                 ToString();
	virtual bool                    operator==(Abstract * xAbstract);
};


#endif