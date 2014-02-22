////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __RUNNABLE_H__
#define __RUNNABLE_H__

//+-----------------------------------------------------------------------------
//
//  Class:  
//      RUNNABLE
//
//  Synopsis:
//      Texture container class.
//
//-----------------------------------------------------------------------------

#include "../_A2DCommon.h"

namespace A2D {

	////////////////////////////////////////////////////////////////////////////////
	// DECLARATION
	////////////////////////////////////////////////////////////////////////////////

	class Runnable
	{
		friend class AbstractThread;
		friend class AbstractEventQueue;

	protected:

		virtual void run(void * x_param, int x_thread_id) IMPLEMENT;

	};
}

#endif