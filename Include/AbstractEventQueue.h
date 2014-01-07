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
#include "OrderedList.h"
#include "Toolkit.h"
#include "Runnable.h"
#include "Rect.h"

#include "ExtLibs.h"

#include "MouseEvent.h"
#include "ActionEvent.h"
#include "FocusEvent.h"
#include "WindowEvent.h"


namespace A2D{

	////////////////////////////////////////////////////////////////////////////////
	// FORWARD DECLARATIONS
	////////////////////////////////////////////////////////////////////////////////

	using namespace A2D;
	class AbstractFrame;
	class AbstractWindow;
	class Window;
	class Component;
	class WindowEvent;

	////////////////////////////////////////////////////////////////////////////////
	// DECLARATION
	////////////////////////////////////////////////////////////////////////////////

	class AbstractEventQueue : public Runnable, public Abstract
	{
	public:

		AbstractEventQueue(AbstractFrame * xFrame);
		~AbstractEventQueue();

	private:

		OrderedList<Runnable*>		 aEventQueue;
		Runnable               *     aImmediateRunnable = NULL;
		AbstractThread		   *     aThread = NULL;

	protected:

		AbstractFrame		  *		aFrame;

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
		virtual bool                    getQueueLock() = 0;
		virtual void					releaseQueueLock() = 0;
		Runnable *						peekEvent();
		void							popEvent();
		bool							hasEvent();

	public:

		// Event handling
		void							processMouseEvent(MouseEvent * xEvent);
		void							processFocusEvent(FocusEvent * xEvent);
		void							processActionEvent(ActionEvent * xEvent);
		void							processWindowEvent(WindowEvent * xEvent);

	private:


		bool							isInvalidLocation(POINT xPoint, OrderedList<Rect*> * xInvalidLocs);

		MouseEvent					*	aMouseEvent; // check performance to see
		FocusEvent					*	aFocusEvent;
		ActionEvent					*	aActionEvent;

		Component					*	aLastFocusedComp = 0;
		Component					*	aLastComponent = 0;
		Rect						*	aLastVisibleRegion = 0;
		//OrderedList<UnorderedList<Component*>*> aComponentLocations;

	protected:

		void							pushEvent(Runnable * xRunnable);
		void							removeAllEvents();
		void							run(int xThreadId);

		virtual AbstractThread*			createPlatformCompatibleThread(Runnable * xRunnable) = 0;

		////////////////////////////////////////////////////////////////////////////////
		// ABSTRACT
		////////////////////////////////////////////////////////////////////////////////

	public:

		virtual HRESULT                 initialize();
		virtual LPCWSTR                 getClass() = 0;
		virtual LPCWSTR                 toString() = 0;

	};
}

#endif
