////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __EVENTQUEUE_H__
#define __EVENTQUEUE_H__

//+-----------------------------------------------------------------------------
//
//  Class:
//      EVENTQUEUE
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

using namespace std;

namespace A2D {

	////////////////////////////////////////////////////////////////////////////////
	// FORWARD DECLARATIONS
	////////////////////////////////////////////////////////////////////////////////

	class Frame;
	class Abstract;
	class Thread;

	////////////////////////////////////////////////////////////////////////////////
	// DECLARATION
	////////////////////////////////////////////////////////////////////////////////

	class EventQueue : public AbstractEventQueue
	{
	public:

		EventQueue::EventQueue(AbstractFrame * xFrame);

		EventQueue::~EventQueue();

	private:

		HANDLE aEventQueueLock;
		HINSTANCE aHIsntance;

	public:

		// Queue
		virtual bool                    getQueueLock();
		virtual void                    releaseQueueLock();

	public:

		// Thread - Move from OS level to Global level!!!
		virtual AbstractThread *		createPlatformCompatibleThread(Runnable * xRunnable);

		////////////////////////////////////////////////////////////////////////////////
		// ABSTRACT
		////////////////////////////////////////////////////////////////////////////////

	public:

		virtual LPCWSTR                 getClass();
		virtual LPCWSTR                 toString();
	};
}

#endif