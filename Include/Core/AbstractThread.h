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
#include "../_A2DCommon.h"

namespace A2D {

	////////////////////////////////////////////////////////////////////////////////
	// DECLARATION
	////////////////////////////////////////////////////////////////////////////////

	class AbstractThread
	{

	public:

		AbstractThread(Runnable * xRunnable);
		virtual ~AbstractThread() IMPLEMENT;

	private:

		Runnable * aRunnable;

		int aId;


	protected:

		static AbstractThread * aSingleton;
		static int aInstanceCount;
		static int aActiveCount;

	public:

		static AbstractThread* getSingleton();
		static int instanceCount();
		static int activeCount();

		void fire();

	public:
		
		virtual int	 id();
		virtual bool start() IMPLEMENT;
		virtual void interrupt() IMPLEMENT;
		virtual void resume() IMPLEMENT;
		virtual void stop() IMPLEMENT;
		virtual bool isAlive() IMPLEMENT;
		virtual void waitAll() IMPLEMENT;
		virtual int getCurrentThreadId() IMPLEMENT;

		////////////////////////////////////////////////////////////////////////////////
		// ABSTRACT
		////////////////////////////////////////////////////////////////////////////////

	public:

		virtual STATUS                 initialize();

	};
}

#endif