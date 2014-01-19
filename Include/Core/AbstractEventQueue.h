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


#include "AbstractThread.h"
#include "OrderedList.h"
#include "Toolkit.h"
#include "Runnable.h"
#include "Rect.h"

#include "ComponentEventSource.h"
#include "MouseEvent.h"
#include "ActionEvent.h"
#include "FocusEvent.h"
#include "WindowEvent.h"

#include "../_A2DCommon.h"

namespace A2D{

	////////////////////////////////////////////////////////////////////////////////
	// FORWARD DECLARATIONS
	////////////////////////////////////////////////////////////////////////////////

	class AbstractFrame;
	class AbstractWindow;
	class Window;
	class WindowEvent;

	////////////////////////////////////////////////////////////////////////////////
	// DECLARATION
	////////////////////////////////////////////////////////////////////////////////

	class AbstractEventQueue : public Runnable
	{

		friend class					AbstractWindow;
		friend class					AbstractFrame;

	public:

		AbstractEventQueue(AbstractFrame * xFrame);
		~AbstractEventQueue();

	private:

		OrderedList<Runnable*>			aEventQueue;
		Runnable               *		aImmediateRunnable = NULL;
		AbstractThread		   *		aThread = NULL;

	protected:

		AbstractFrame		  *			aFrame;

	public:

		void                            invokeLater(Runnable * xRunnable);
		void                            invokeAndWait(Runnable * xRunnable);
		void                            clearQueue();
		bool							dispatchNextEvent();
		AbstractThread		 *			getDispatchingThread();

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

		static AbstractEventQueue*		aClassInstance;
		static AbstractEventQueue*		getInstance();


	public:

		// Queue
		virtual bool                    getQueueLock() IMPLEMENT;
		virtual void					releaseQueueLock() IMPLEMENT;
		Runnable *						peekEvent();
		void							popEvent();
		bool							hasEvent();

	public:

		// Event handling
		void							processMouseEvent(MouseEvent * xEvent);
		void							processFocusEvent(FocusEvent * xEvent);
		STATUS							processActionEvent(ActionEvent * xEvent);
		void							processWindowEvent(WindowEvent * xEvent);
		void							processMouseMotionEvent(MouseEvent * xEvent);

		void							addEventDepthTracker(Component * xSource, float xZ);
		void							removeEventDepthTracker(Component * xSource, float xZ);

		Component					*	findNextCompListener(Component * xSource);
		Component					*	findPrevCompListener(Component * xSource);

	private:

		bool							hasListener(EventSource * xSource);

		bool							aMousePressed = false;
		MouseEvent					*	aMouseEvent; 
		FocusEvent					*	aFocusEvent;
		ActionEvent					*	aActionEvent;

		Component					*	aLastFocusedComp = 0;
		EventSource					*	aLastSource = 0;
		Rect						*	aLastVisibleRegion = 0;
		OrderedList<OrderedList<Component*>*> aComponentEventSources;
		OrderedList<EventSource *>		aEventSourcesList;

	protected:

		void							pushEvent(Runnable * xRunnable);
		void							removeAllEvents();
		void							run(int xThreadId);

		virtual AbstractThread*			createPlatformCompatibleThread(Runnable * xRunnable) IMPLEMENT;

		////////////////////////////////////////////////////////////////////////////////
		// ABSTRACT
		////////////////////////////////////////////////////////////////////////////////

	public:

		virtual STATUS                 initialize();

	};
}

#endif
