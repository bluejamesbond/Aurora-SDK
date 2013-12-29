////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __ABSTRACTEVENTQUEUE_H__
#define __ABSTRACTEVENTQUEUE_H__

//+-----------------------------------------------------------------------------
//
//  Abstract Class:
//      ABSTRACTEVENTQUEUE
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
#include "Renderable.h"
#include "AbstractThread.h"
#include "Toolkit.h"
#include "Runnable.h"
#include "Rect.h"

namespace A2D{

	////////////////////////////////////////////////////////////////////////////////
	// FORWARD DECLARATIONS
	////////////////////////////////////////////////////////////////////////////////

	class AbstractFrame;
	class AbstractWindow;
	class Window;

	////////////////////////////////////////////////////////////////////////////////
	// DECLARATION
	////////////////////////////////////////////////////////////////////////////////

	class AbstractEventQueue : public Runnable, public Abstract
	{
	public:

		AbstractEventQueue(AbstractFrame * xFrame);

	private:

		Runnable               *     aImmediateRunnable = NULL;
		AbstractThread		  *		aThread = NULL;

	protected:

		AbstractFrame		  *		aFrame;

	public:

		void                            invokeLater(Runnable * xRunnable);
		void                            invokeAndWait(Runnable * xRunnable);
		void                            clearQueue();
		bool							dispatchNextEvent();
		AbstractThread		 *		getDispatchingThread();

		static bool						isDispatchingThread(int xFrameId);
		void							invokeRerender();
		void							invokeRevalidate();
		void							invokeReset();

		void                            invokeAnimationFrame(int xTime, Runnable * xRunnable);

		int		 						waitForAllDispatchingThreads();

		void							startDispatchingThread();
		void							stopDispatchingThread();
		void							interruptDispatchingThread();
		void							resumeDispatchingThread();

		static AbstractEventQueue*	aClassInstance;
		static AbstractEventQueue*	getInstance();

		// Queue

	public:

		virtual bool                    getQueueLock() = 0;
		virtual void                    releaseQueueLock() = 0;
		virtual Runnable *           peekEvent() = 0;
		virtual void					popEvent() = 0;
		virtual bool                    hasEvent() = 0;

	protected:

		virtual void                    pushEvent(Runnable * xRunnable) = 0;
		virtual void                    removeAllEvents() = 0;
		virtual void					run(int xThreadId);

		// Creators
		virtual AbstractThread*		createPlatformCompatibleThread(Runnable * xRunnable) = 0;

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
}

#endif
