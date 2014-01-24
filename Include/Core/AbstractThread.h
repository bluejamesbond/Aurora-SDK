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

#include "Runnable.h"
#include "Common.h"

namespace A2D {

	////////////////////////////////////////////////////////////////////////////////
	// DECLARATION
	////////////////////////////////////////////////////////////////////////////////

	class AbstractThread
	{

	public:

		AbstractThread(Runnable * xRunnable);
		virtual ~AbstractThread() = 0;

	private:

		Runnable * aRunnable;

	protected:

		static AbstractThread * aSingleton;
		static int aInstanceCount;
		static int aActiveCount;

		int aId;

	public:

		static AbstractThread* getSingleton();
		static int instanceCount();
		static int activeCount();

		void fire();

	public:
		
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

		virtual HRESULT                 initialize();

	};
}

#endif
